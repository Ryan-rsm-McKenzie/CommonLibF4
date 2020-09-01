[[nodiscard]] auto& get_iddb()
{
	static REL::IDDatabase::Offset2ID iddb;
	return iddb;
}

class VTable
{
public:
	VTable(std::string_view a_name, std::uint32_t a_offset = 0)
	{
		const auto typeDesc = type_descriptor(a_name);
		const auto col = complete_object_locator(typeDesc, a_offset);
		const auto vtbl = virtual_table(col);
		_address = reinterpret_cast<std::uintptr_t>(vtbl);
	}

	[[nodiscard]] constexpr std::uintptr_t address() const noexcept { return _address; }
	[[nodiscard]] std::uintptr_t offset() const noexcept { return address() - REL::Module::get().base(); }

private:
	[[nodiscard]] const RE::RTTI::TypeDescriptor* type_descriptor(std::string_view a_name) const
	{
		const auto segment = REL::Module::get().segment(REL::Segment::data);
		const stl::span haystack{ segment.pointer<const char>(), segment.size() };

		boost::algorithm::knuth_morris_pratt search(a_name.cbegin(), a_name.cend());
		const auto it = search(haystack.cbegin(), haystack.cend());

		if (it.first == it.second) {
			throw std::runtime_error("failed to find type descriptor"s);
		}

		return reinterpret_cast<const RE::RTTI::TypeDescriptor*>(
			it.first -
			offsetof(RE::RTTI::TypeDescriptor, name));
	}

	[[nodiscard]] const RE::RTTI::CompleteObjectLocator* complete_object_locator(const RE::RTTI::TypeDescriptor* a_typeDesc, std::uint32_t a_offset) const
	{
		assert(a_typeDesc != nullptr);

		const auto& module = REL::Module::get();
		const auto typeDesc = reinterpret_cast<std::uintptr_t>(a_typeDesc);
		const auto rva = static_cast<std::uint32_t>(typeDesc - module.base());

		const auto segment = module.segment(REL::Segment::rdata);
		const auto base = segment.pointer<const std::byte>();
		const auto start = reinterpret_cast<const std::uint32_t*>(base);
		const auto end = reinterpret_cast<const std::uint32_t*>(base + segment.size());

		for (auto iter = start; iter < end; ++iter) {
			if (*iter == rva) {
				// both base class desc and col can point to the type desc so we check
				// the next int to see if it can be an rva to decide which type it is
				if ((iter[1] < segment.offset()) || (segment.offset() + segment.size() <= iter[1])) {
					continue;
				}

				const auto ptr = reinterpret_cast<const std::byte*>(iter);
				const auto col = reinterpret_cast<const RE::RTTI::CompleteObjectLocator*>(ptr - offsetof(RE::RTTI::CompleteObjectLocator, typeDescriptor));
				if (col->offset != a_offset) {
					continue;
				}

				return col;
			}
		}

		throw std::runtime_error("failed to find complete object locator"s);
	}

	[[nodiscard]] const void* virtual_table(const RE::RTTI::CompleteObjectLocator* a_col) const
	{
		assert(a_col != nullptr);

		const auto col = reinterpret_cast<std::uintptr_t>(a_col);

		const auto segment = REL::Module::get().segment(REL::Segment::rdata);
		const auto base = segment.pointer<const std::byte>();
		const auto start = reinterpret_cast<const std::uintptr_t*>(base);
		const auto end = reinterpret_cast<const std::uintptr_t*>(base + segment.size());

		for (auto iter = start; iter < end; ++iter) {
			if (*iter == col) {
				return iter + 1;
			}
		}

		throw std::runtime_error("failed to find virtual table"s);
	}

	std::uintptr_t _address{ 0 };
};

[[nodiscard]] inline std::string sanitize_name(std::string a_name)
{
	static const std::array expressions{
		std::make_pair(
			boost::regex{ R"regex((`anonymous namespace'|[ &'*\-`]){1})regex"s, boost::regex::ECMAScript | boost::regex::optimize },
			std::function{ [](std::string& a_name, const boost::ssub_match& a_match) {
				a_name.erase(a_match.first, a_match.second);
			} }),
		std::make_pair(
			boost::regex{ R"regex(([(),:<>]){1})regex"s, boost::regex::ECMAScript | boost::regex::optimize },
			std::function{ [](std::string& a_name, const boost::ssub_match& a_match) {
				a_name.replace(a_match.first, a_match.second, "_"sv);
			} }),
	};

	boost::smatch matches;
	for (const auto& [expr, callback] : expressions) {
		while (boost::regex_search(a_name, matches, expr)) {
			for (std::size_t i = 1; i < matches.size(); ++i) {
				callback(a_name, matches[static_cast<int>(i)]);
			}
		}
	}

	return a_name;
}

[[nodiscard]] inline std::string decode_name(const RE::RTTI::TypeDescriptor* a_typeDesc)
{
	assert(a_typeDesc != nullptr);

	std::array<char, 0x1000> buf;
	const auto len =
		WinAPI::UnDecorateSymbolName(
			a_typeDesc->name + 1,
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

[[nodiscard]] inline bool starts_with(std::string_view a_haystack, std::string_view a_needle)
{
	if (a_haystack.length() >= a_needle.length()) {
		return a_haystack.substr(0, a_needle.length()) == a_needle;
	} else {
		return false;
	}
}

inline void dump_rtti()
{
	std::vector<std::pair<std::string, std::uint64_t>> results;

	VTable typeInfo(".?AVtype_info@@"sv);
	const auto& module = REL::Module::get();
	const auto baseAddr = module.base();
	const auto data = module.segment(REL::Segment::data);
	const auto beg = data.pointer<const std::uintptr_t>();
	const auto end = reinterpret_cast<const std::uintptr_t*>(data.address() + data.size());
	const auto& iddb = get_iddb();
	for (auto iter = beg; iter < end; ++iter) {
		if (*iter == typeInfo.address()) {
			const auto typeDescriptor = reinterpret_cast<const RE::RTTI::TypeDescriptor*>(iter);
			try {
				const auto id = iddb(reinterpret_cast<std::uintptr_t>(iter) - baseAddr);
				auto name = decode_name(typeDescriptor);
				results.emplace_back(sanitize_name(std::move(name)), id);
			} catch (const std::exception&) {
				logger::error(decode_name(typeDescriptor));
				continue;
			}
		}
	}

	std::sort(results.begin(), results.end());
	const auto it = std::unique(
		results.begin(),
		results.end(),
		[](auto&& a_lhs, auto&& a_rhs) {
			return a_lhs.first == a_rhs.first;
		});
	results.erase(it, results.end());

	std::ofstream file("RTTI_IDs.h"sv);
	file << "#pragma once\n"sv
		 << "\n"sv
		 << "namespace RE\n"sv
		 << "{\n"sv;
	for (auto& result : results) {
		file << "\tinline constexpr REL::ID RTTI_"sv << result.first << "{ "sv << result.second << " };\n"sv;
	}
	file << "}\n"sv;
}

inline void dump_nirtti()
{
	{
		// fix a dumb fuckup
		REL::Relocation<RE::NiRTTI*> rtti{ REL::ID(221529) };
		rtti->name = "BGSStaticCollection::RootFacade";
	}

	constexpr std::array seeds = {
		17735,	  // NiObject
		1352616,  // NiCullingProcess
		31936,	  // BSFaceGenMorphData
		1482971,  // BSTempEffect
		1123991,  // bhkCharacterProxy
		858091,	  // bhkCharacterRigidBody
		933986,	  // bhkNPCollisionObject
		56458,	  // bhkNPCollisionObjectBase
		1372534,  // bhkNPCollisionObjectUnlinked
		495124,	  // bhkNPCollisionProxyObject
		1325961,  // bhkPhysicsSystem
		182826,	  // bhkRagdollSystem
		1359461,  // bhkWorld
		34089,	  // bhkWorldM
	};
	robin_hood::unordered_flat_set<std::uintptr_t> results;
	results.reserve(seeds.size());
	for (const auto& seed : seeds) {
		results.insert(REL::ID(seed).address());
	}

	const auto& module = REL::Module::get();
	const auto base = module.base();
	const auto segment = module.segment(REL::Segment::data);
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
		std::string name("NiRTTI_"sv);
		name += rtti->GetName();
		try {
			const auto id = iddb(result - base);
			toPrint.emplace_back(sanitize_name(std::move(name)), id);
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
		   << "{\n"sv;
	for (const auto& elem : toPrint) {
		output << "\tinline constexpr REL::ID "sv << elem.first << "{ "sv << elem.second << " };\n"sv;
	}
	output << "}\n"sv;
}

inline void MessageHandler(F4SE::MessagingInterface::Message* a_message)
{
	switch (a_message->type) {
	case F4SE::MessagingInterface::kGameDataReady:
		try {
			dump_rtti();
			dump_nirtti();
		} catch (const std::exception& e) {
			logger::error(e.what());
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
