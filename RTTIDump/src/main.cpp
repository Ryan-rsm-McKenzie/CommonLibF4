[[nodiscard]] auto& get_iddb()
{
	static REL::IDDatabase::Offset2ID iddb;
	return iddb;
}

class VTable
{
public:
	using container_type = std::vector<REL::Relocation<const void*>>;
	using size_type = typename container_type::size_type;
	using value_type = typename container_type::value_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	using iterator = typename container_type::iterator;
	using const_iterator = typename container_type::const_iterator;

	VTable(std::string_view a_name) :
		VTable(type_descriptor(a_name))
	{}

	VTable(const RE::RTTI::TypeDescriptor* a_typeDescriptor)
	{
		auto cols = complete_object_locators(a_typeDescriptor);
		_vtables = virtual_tables({ cols.data(), cols.size() });
	}

	[[nodiscard]] reference operator[](std::size_t a_idx) noexcept { return _vtables[a_idx]; }
	[[nodiscard]] const_reference operator[](std::size_t a_idx) const noexcept { return _vtables[a_idx]; }

	[[nodiscard]] iterator begin() noexcept { return _vtables.begin(); }
	[[nodiscard]] const_iterator begin() const noexcept { return _vtables.begin(); }
	[[nodiscard]] const_iterator cbegin() const noexcept { return _vtables.cbegin(); }

	[[nodiscard]] iterator end() noexcept { return _vtables.end(); }
	[[nodiscard]] const_iterator end() const noexcept { return _vtables.end(); }
	[[nodiscard]] const_iterator cend() const noexcept { return _vtables.cend(); }

	[[nodiscard]] size_type size() const noexcept { return _vtables.size(); }

private:
	[[nodiscard]] static const RE::RTTI::TypeDescriptor* type_descriptor(std::string_view a_name)
	{
		const auto segment = REL::Module::get().segment(REL::Segment::data);
		const std::span haystack{ segment.pointer<const char>(), segment.size() };

		std::boyer_moore_horspool_searcher searcher(a_name.cbegin(), a_name.cend());
		const auto [first, last] = searcher(haystack.begin(), haystack.end());

		if (first == last) {
			throw std::runtime_error("failed to find type descriptor"s);
		} else {
			return reinterpret_cast<const RE::RTTI::TypeDescriptor*>(std::to_address(first) - 0x10);
		}
	}

	[[nodiscard]] static std::vector<const RE::RTTI::CompleteObjectLocator*> complete_object_locators(const RE::RTTI::TypeDescriptor* a_typeDesc)
	{
		assert(a_typeDesc != nullptr);

		const auto& mod = REL::Module::get();
		const auto typeDesc = reinterpret_cast<std::uintptr_t>(a_typeDesc);
		const auto rva = static_cast<std::uint32_t>(typeDesc - mod.base());

		const auto segment = mod.segment(REL::Segment::rdata);
		const auto base = segment.pointer<const std::byte>();
		const auto start = reinterpret_cast<const std::uint32_t*>(base);
		const auto end = reinterpret_cast<const std::uint32_t*>(base + segment.size());

		std::vector<const RE::RTTI::CompleteObjectLocator*> results;

		for (auto iter = start; iter < end; ++iter) {
			if (*iter == rva) {
				// both base class desc and col can point to the type desc so we check
				// the next int to see if it can be an rva to decide which type it is
				if ((iter[1] < segment.offset()) || (segment.offset() + segment.size() <= iter[1])) {
					continue;
				}

				const auto ptr = reinterpret_cast<const std::byte*>(iter);
				const auto col = reinterpret_cast<const RE::RTTI::CompleteObjectLocator*>(ptr - offsetof(RE::RTTI::CompleteObjectLocator, typeDescriptor));
				results.push_back(col);
			}
		}

		return results;
	}

	[[nodiscard]] static container_type virtual_tables(std::span<const RE::RTTI::CompleteObjectLocator*> a_cols)
	{
		assert(std::all_of(a_cols.begin(), a_cols.end(), [](auto&& a_elem) noexcept { return a_elem != nullptr; }));

		const auto segment = REL::Module::get().segment(REL::Segment::rdata);
		const auto base = segment.pointer<const std::byte>();
		const auto start = reinterpret_cast<const std::uintptr_t*>(base);
		const auto end = reinterpret_cast<const std::uintptr_t*>(base + segment.size());

		container_type results;

		for (auto iter = start; iter < end; ++iter) {
			if (std::find_if(
					a_cols.begin(),
					a_cols.end(),
					[&](const RE::RTTI::CompleteObjectLocator* a_col) noexcept {
						return *iter == reinterpret_cast<std::uintptr_t>(a_col);
					}) != a_cols.end()) {
				results.emplace_back(reinterpret_cast<std::uintptr_t>(iter + 1));
			}
		}

		if (results.size() != a_cols.size()) {
			throw std::runtime_error("failed to find virtual tables"s);
		} else {
			std::sort(
				results.begin(),
				results.end(),
				[](auto&& a_lhs, auto&& a_rhs) {
					return a_lhs.address() < a_rhs.address();
				});
			return results;
		}
	}

	container_type _vtables;
};

[[nodiscard]] std::string sanitize_name(std::string a_name)
{
	static const std::array expressions{
		std::make_pair(
			srell::regex{ R"regex((`anonymous namespace'|[ &'*\-`]){1})regex"s, srell::regex::ECMAScript },
			std::function{ [](std::string& a_name, const srell::ssub_match& a_match) {
				a_name.erase(a_match.first, a_match.second);
			} }),
		std::make_pair(
			srell::regex{ R"regex(([(),:<>]){1})regex"s, srell::regex::ECMAScript },
			std::function{ [](std::string& a_name, const srell::ssub_match& a_match) {
				a_name.replace(a_match.first, a_match.second, "_"sv);
			} }),
	};

	srell::smatch matches;
	for (const auto& [expr, callback] : expressions) {
		while (srell::regex_search(a_name, matches, expr)) {
			for (std::size_t i = 1; i < matches.size(); ++i) {
				callback(a_name, matches[static_cast<int>(i)]);
			}
		}
	}

	return a_name;
}

[[nodiscard]] std::string decode_name(const RE::RTTI::TypeDescriptor* a_typeDesc)
{
	assert(a_typeDesc != nullptr);

	std::array<char, 0x1000> buf;
	const auto len =
		WinAPI::UnDecorateSymbolName(
			a_typeDesc->mangled_name() + 1,
			buf.data(),
			static_cast<std::uint32_t>(buf.size()),
			(WinAPI::UNDNAME_NO_MS_KEYWORDS) |
				(WinAPI::UNDNAME_NO_FUNCTION_RETURNS) |
				(WinAPI::UNDNAME_NO_ALLOCATION_MODEL) |
				(WinAPI::UNDNAME_NO_ALLOCATION_LANGUAGE) |
				(WinAPI::UNDNAME_NO_THISTYPE) |
				(WinAPI::UNDNAME_NO_ACCESS_SPECIFIERS) |
				(WinAPI::UNDNAME_NO_THROW_SIGNATURES) |
				(WinAPI::UNDNAME_NO_RETURN_UDT_MODEL) |
				(WinAPI::UNDNAME_NAME_ONLY) |
				(WinAPI::UNDNAME_NO_ARGUMENTS) |
				static_cast<std::uint32_t>(0x8000));  // Disable enum/class/struct/union prefix

	if (len != 0) {
		return { buf.data(), len };
	} else {
		throw std::runtime_error("failed to decode name"s);
	}
}

[[nodiscard]] bool starts_with(std::string_view a_haystack, std::string_view a_needle)
{
	if (a_haystack.length() >= a_needle.length()) {
		return a_haystack.substr(0, a_needle.length()) == a_needle;
	} else {
		return false;
	}
}

void dump_rtti()
{
	std::vector<std::tuple<std::string, std::uint64_t, std::vector<std::uint64_t>>> results;  // [ demangled name, rtti id, vtable ids ]

	VTable typeInfo(".?AVtype_info@@"sv);
	const auto& mod = REL::Module::get();
	const auto baseAddr = mod.base();
	const auto data = mod.segment(REL::Segment::data);
	const auto beg = data.pointer<const std::uintptr_t>();
	const auto end = reinterpret_cast<const std::uintptr_t*>(data.address() + data.size());
	const auto& iddb = get_iddb();
	for (auto iter = beg; iter < end; ++iter) {
		if (*iter == typeInfo[0].address()) {
			const auto typeDescriptor = reinterpret_cast<const RE::RTTI::TypeDescriptor*>(iter);
			try {
				auto name = decode_name(typeDescriptor);
				const auto rid = iddb(reinterpret_cast<std::uintptr_t>(iter) - baseAddr);

				VTable vtable{ typeDescriptor };
				std::vector<std::uint64_t> vids(vtable.size());
				std::transform(
					vtable.begin(),
					vtable.end(),
					vids.begin(),
					[&](auto&& a_elem) { return iddb(a_elem.offset()); });

				results.emplace_back(sanitize_name(std::move(name)), rid, std::move(vids));
			} catch (const std::exception&) {
				logger::error("{}"sv, decode_name(typeDescriptor));
				continue;
			}
		}
	}

	std::sort(results.begin(), results.end());
	results.erase(
		std::unique(
			results.begin(),
			results.end(),
			[](auto&& a_lhs, auto&& a_rhs) {
				return std::get<0>(a_lhs) == std::get<0>(a_rhs);
			}),
		results.end());

	constexpr std::array toRemove{
		static_cast<std::uint64_t>(25921),   // float
		static_cast<std::uint64_t>(950502),  // unsigned int
	};
	results.erase(
		std::remove_if(
			results.begin(),
			results.end(),
			[&](auto&& a_elem) {
				return std::find(toRemove.begin(), toRemove.end(), std::get<1>(a_elem)) != toRemove.end();
			}),
		results.end());

	std::ofstream file;
	const auto openf = [&](std::string_view a_name) {
		file.open(a_name.data() + "_IDs.h"s);
		file << "#pragma once\n"sv
			 << "\n"sv
			 << "namespace RE\n"sv
			 << "{\n"sv
			 << "\tnamespace "sv << a_name << "\n"sv
			 << "\t{\n"sv;
	};
	const auto closef = [&]() {
		file << "\t}\n"sv
			 << "}\n"sv;
		file.close();
	};

	openf("RTTI"sv);
	for (const auto& [name, rid, vids] : results) {
		(void)vids;
		file << "\t\tinline constexpr REL::ID "sv << name << "{ "sv << rid << " };\n"sv;
	}
	closef();

	openf("VTABLE"sv);
	const auto printVID = [&](std::uint64_t a_vid) { file << "REL::ID("sv << a_vid << ")"sv; };
	for (const auto& [name, rid, vids] : results) {
		(void)rid;
		const std::span svids{ vids.data(), vids.size() };
		if (!svids.empty()) {
			file << "\t\tinline constexpr std::array<REL::ID, "sv
				 << vids.size()
				 << "> "sv
				 << name
				 << "{ "sv;
			printVID(svids.front());
			for (const auto vid : svids.subspan(1)) {
				file << ", "sv;
				printVID(vid);
			}
			file << " };\n"sv;
		}
	}
	closef();
}

void dump_nirtti()
{
	{
		// fix a dumb fuckup
		REL::Relocation<RE::NiRTTI*> rtti{ REL::ID(221529) };
		rtti->name = "BGSStaticCollection::RootFacade";
	}

	constexpr std::array seeds = {
		17735,    // NiObject
		1352616,  // NiCullingProcess
		31936,    // BSFaceGenMorphData
		1482971,  // BSTempEffect
		1123991,  // bhkCharacterProxy
		858091,   // bhkCharacterRigidBody
		933986,   // bhkNPCollisionObject
		56458,    // bhkNPCollisionObjectBase
		1372534,  // bhkNPCollisionObjectUnlinked
		495124,   // bhkNPCollisionProxyObject
		1325961,  // bhkPhysicsSystem
		182826,   // bhkRagdollSystem
		1359461,  // bhkWorld
		34089,    // bhkWorldM
	};
	robin_hood::unordered_flat_set<std::uintptr_t> results;
	results.reserve(seeds.size());
	for (const auto& seed : seeds) {
		results.insert(REL::ID(seed).address());
	}

	const auto& mod = REL::Module::get();
	const auto base = mod.base();
	const auto segment = mod.segment(REL::Segment::data);
	const auto beg = segment.pointer<const std::uintptr_t>();
	const auto end = reinterpret_cast<const std::uintptr_t*>(segment.address() + segment.size());
	bool found = false;
	do {
		found = false;
		for (auto iter = beg; iter < end; ++iter) {
			if (results.find(*iter) != results.end()) {
				const auto ins = results.insert(reinterpret_cast<std::uintptr_t>(iter - 1));
				if (!found) {
					found = ins.second;
				}
			}
		}
	} while (found);

	std::vector<std::pair<std::string, std::uint64_t>> toPrint;
	const auto& iddb = get_iddb();
	for (const auto& result : results) {
		const auto rtti = reinterpret_cast<const RE::NiRTTI*>(result);
		try {
			const auto id = iddb(result - base);
			toPrint.emplace_back(sanitize_name(rtti->GetName()), id);
		} catch (const std::exception&) {
			spdlog::error(rtti->GetName());
		}
	}

	const auto comp =
		[](auto&& a_lhs, auto&& a_rhs) {
			return a_lhs.first < a_rhs.first;
		};
	std::sort(toPrint.begin(), toPrint.end(), comp);

	std::ofstream output("NiRTTI_IDs.h");
	output << "#pragma once\n"sv
		   << "\n"sv
		   << "namespace RE\n"sv
		   << "{\n"sv
		   << "\tnamespace Ni_RTTI\n"sv
		   << "\t{\n"sv;
	for (const auto& elem : toPrint) {
		output << "\t\tinline constexpr REL::ID "sv << elem.first << "{ "sv << elem.second << " };\n"sv;
	}
	output << "\t}\n"sv
		   << "}\n"sv;
}

void MessageHandler(F4SE::MessagingInterface::Message* a_message)
{
	switch (a_message->type) {
	case F4SE::MessagingInterface::kGameDataReady:
		try {
			dump_rtti();
			dump_nirtti();
		} catch (const std::exception& e) {
			logger::error("{}"sv, e.what());
		}
		break;
	default:
		break;
	}
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		return false;
	}

	*path /= "RTTIDump.log"sv;
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log", std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::warn);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v");

	a_info->infoVersion = F4SE::PluginInfo::kVersion;
	a_info->name = "ExampleProject";
	a_info->version = 1;

	if (a_f4se->IsEditor()) {
		logger::critical("loaded in editor");
		return false;
	}

	const auto ver = a_f4se->RuntimeVersion();
	if (ver < F4SE::RUNTIME_1_10_130) {
		logger::critical("unsupported runtime v{}", ver.string());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se);

	auto messaging = F4SE::GetMessagingInterface();
	messaging->RegisterListener(MessageHandler);

	return true;
}
