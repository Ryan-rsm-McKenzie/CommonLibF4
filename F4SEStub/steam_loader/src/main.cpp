namespace stl
{
	template <class EF>                                    //
	requires(std::invocable<std::remove_reference_t<EF>>)  //
		class scope_exit
	{
	public:
		// 1)
		template <class Fn>
		explicit scope_exit(Fn&& a_fn)  //
			noexcept(std::is_nothrow_constructible_v<EF, Fn> ||
					 std::is_nothrow_constructible_v<EF, Fn&>)  //
			requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_exit> &&
					 std::is_constructible_v<EF, Fn>)
		{
			static_assert(std::invocable<Fn>);

			if constexpr (!std::is_lvalue_reference_v<Fn> &&
						  std::is_nothrow_constructible_v<EF, Fn>) {
				_fn.emplace(std::forward<Fn>(a_fn));
			} else {
				_fn.emplace(a_fn);
			}
		}

		// 2)
		scope_exit(scope_exit&& a_rhs)  //
			noexcept(std::is_nothrow_move_constructible_v<EF> ||
					 std::is_nothrow_copy_constructible_v<EF>)  //
			requires(std::is_nothrow_move_constructible_v<EF> ||
					 std::is_copy_constructible_v<EF>)
		{
			static_assert(!(std::is_nothrow_move_constructible_v<EF> && !std::is_move_constructible_v<EF>));
			static_assert(!(!std::is_nothrow_move_constructible_v<EF> && !std::is_copy_constructible_v<EF>));

			if (a_rhs.active()) {
				if constexpr (std::is_nothrow_move_constructible_v<EF>) {
					_fn.emplace(std::forward<EF>(*a_rhs._fn));
				} else {
					_fn.emplace(a_rhs._fn);
				}
				a_rhs.release();
			}
		}

		// 3)
		scope_exit(const scope_exit&) = delete;

		~scope_exit() noexcept
		{
			if (_fn.has_value()) {
				(*_fn)();
			}
		}

		void release() noexcept { _fn.reset(); }

	private:
		[[nodiscard]] bool active() const noexcept { return _fn.has_value(); }

		std::optional<std::remove_reference_t<EF>> _fn;
	};

	template <class EF>
	scope_exit(EF) -> scope_exit<EF>;
}

namespace unicode
{
	using nowide::cerr;
	using nowide::narrow;
	using nowide::widen;

	[[nodiscard]] std::string narrow(std::wstring_view a_str)
	{
		return nowide::narrow(a_str.data(), a_str.size());
	}

	[[nodiscard]] std::wstring widen(std::string_view a_str)
	{
		return nowide::widen(a_str.data(), a_str.size());
	}
}

namespace win32
{
	namespace detail
	{
		[[noreturn]] void error(std::string_view a_error)
		{
			throw std::runtime_error{
				fmt::format(
					FMT_STRING("{:08X}: {}"),
					::GetLastError(),
					a_error)
			};
		}
	}

	struct module_t;
	using proc_t = void (*)();

	[[nodiscard]] auto get_environment_variable(std::string_view a_variable)
		-> std::string
	{
		const auto var = unicode::widen(a_variable);
		const auto len = ::GetEnvironmentVariableW(
			var.c_str(),
			nullptr,
			0);
		if (len == 0) {
			detail::error("failed to get environment variable buffer size"sv);
		}

		std::wstring result(static_cast<std::size_t>(len - 1), '\0');
		if (::GetEnvironmentVariableW(
				var.c_str(),
				result.data(),
				static_cast<::DWORD>(result.size() + 1)) == 0) {
			detail::error("failed to get environment variable"sv);
		}

		return unicode::narrow(result);
	}

	[[nodiscard]] auto get_known_folder_path()
		-> std::filesystem::path
	{
		wchar_t* path = nullptr;
		const stl::scope_exit _([&]() { if (path) { ::CoTaskMemFree(path); } });
		if (SHGetKnownFolderPath(
				FOLDERID_Documents,
				KNOWN_FOLDER_FLAG::KF_FLAG_DEFAULT,
				nullptr,
				&path) != S_OK) {
			detail::error("failed to get known folder path"sv);
		}

		std::filesystem::path result = path;
		return result;
	}

	/*
	* @pre a_mod is a valid module
	* @post result NOT null
	*/
	[[nodiscard]] module_t* get_module_handle(std::string_view a_mod)
	{
		const auto mod = unicode::widen(a_mod);
		const auto handle = ::GetModuleHandleW(mod.c_str());
		if (!handle) {
			detail::error("failed to get module handle"sv);
		} else {
			return reinterpret_cast<module_t*>(handle);
		}
	}

	/*
	* @pre a_module is NOT null
	* @post result NOT null
	*/
	[[nodiscard]] proc_t* get_proc_address(
		module_t* a_module,
		std::string_view a_name)
	{
		assert(a_module != nullptr);

		const auto proc = ::GetProcAddress(
			reinterpret_cast<::HMODULE>(a_module),
			a_name.data());
		if (!proc) {
			detail::error("failed to get proc address"sv);
		} else {
			return reinterpret_cast<proc_t*>(proc);
		}
	}

	[[nodiscard]] auto load_library(std::string_view a_library)
	{
		const auto lib = unicode::widen(a_library);
		const auto mod = ::LoadLibraryW(lib.c_str());
		if (mod == nullptr) {
			detail::error("failed to load library ({})"sv);
		}

		const auto free = [](module_t* a_module) {
			if (a_module &&
				::FreeLibrary(
					reinterpret_cast<::HMODULE>(a_module)) == 0) {
				detail::error("failed to free library"sv);
			}
		};

		return std::unique_ptr<module_t, decltype(free)>{
			reinterpret_cast<module_t*>(mod),
			free
		};
	}

	/*
	* @pre a_range is NOT empty
	*/
	std::uint32_t virtual_protect(
		std::span<std::byte> a_range,
		std::uint32_t a_protections)
	{
		assert(!a_range.empty());

		::DWORD old = 0;
		if (::VirtualProtect(
				a_range.data(),
				a_range.size(),
				a_protections,
				&old) == 0) {
			detail::error("failed to virtual protect memory"sv);
		}

		return static_cast<std::uint32_t>(old);
	}
}

namespace util
{
	template <class T, class U>
	[[nodiscard]] auto adjust_pointer(U* a_ptr, std::ptrdiff_t a_adjust) noexcept
	{
		const auto addr = a_ptr ? reinterpret_cast<std::uintptr_t>(a_ptr) + a_adjust : 0;
		if constexpr (std::is_const_v<U> && std::is_volatile_v<U>) {
			return reinterpret_cast<std::add_cv_t<T>*>(addr);
		} else if constexpr (std::is_const_v<U>) {
			return reinterpret_cast<std::add_const_t<T>*>(addr);
		} else if constexpr (std::is_volatile_v<U>) {
			return reinterpret_cast<std::add_volatile_t<T>*>(addr);
		} else {
			return reinterpret_cast<T*>(addr);
		}
	}

	template <class T>
	[[noreturn]] void error(T&& a_error)
	{
		throw std::runtime_error{ std::string(std::forward<T>(a_error)) };
	}

	template <class... Args>
	[[noreturn]] void error(fmt::format_string<Args...> a_fmt, Args&&... a_args)
	{
		throw std::runtime_error{
			fmt::format(a_fmt, std::forward<Args>(a_args)...)
		};
	}

	void safe_write(
		std::uintptr_t a_dst,
		const void* a_src,
		std::size_t a_size)
	{
		const auto range = std::span{ reinterpret_cast<std::byte*>(a_dst), a_size };
		const auto protections = win32::virtual_protect(range, PAGE_EXECUTE_READWRITE);
		const stl::scope_exit restore([&]() { win32::virtual_protect(range, protections); });
		std::memcpy(
			reinterpret_cast<void*>(a_dst),
			a_src,
			a_size);
	}

	template <std::integral T>
	void safe_write(std::uintptr_t a_dst, T a_src)
	{
		safe_write(a_dst, std::addressof(a_src), sizeof(T));
	}
}

// https://guidedhacking.com/attachments/pe_imptbl_headers-jpg.2241/
void* get_iat(
	win32::module_t* a_module,
	std::string_view a_dll,
	std::string_view a_function)
{
	assert(a_module != nullptr);
	const auto dosHeader = reinterpret_cast<::IMAGE_DOS_HEADER*>(a_module);
	if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		util::error("invalid dos header"sv);
	}

	const auto ntHeader = util::adjust_pointer<::IMAGE_NT_HEADERS>(dosHeader, dosHeader->e_lfanew);
	const auto& dataDir = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	const auto importDesc = util::adjust_pointer<::IMAGE_IMPORT_DESCRIPTOR>(dosHeader, dataDir.VirtualAddress);

	for (auto import = importDesc; import->Characteristics != 0; ++import) {
		const auto name = util::adjust_pointer<const char>(dosHeader, import->Name);
		if (_stricmp(a_dll.data(), name) != 0) {
			continue;
		}

		const auto thunk = util::adjust_pointer<::IMAGE_THUNK_DATA>(dosHeader, import->OriginalFirstThunk);
		for (std::size_t i = 0; thunk[i].u1.Ordinal; ++i) {
			if (IMAGE_SNAP_BY_ORDINAL(thunk[i].u1.Ordinal)) {
				continue;
			}

			const auto importByName = util::adjust_pointer<IMAGE_IMPORT_BY_NAME>(dosHeader, thunk[i].u1.AddressOfData);
			if (_stricmp(a_function.data(), importByName->Name) == 0) {
				return util::adjust_pointer<::IMAGE_THUNK_DATA>(dosHeader, import->FirstThunk) + i;
			}
		}
	}

	util::error("failed to find {}!{}"sv, a_dll, a_function);
}

void initialize_log()
{
	auto path = win32::get_known_folder_path();
	path /= "My Games/Fallout4/F4SE/f4se_steam_loader.log"sv;
	spdlog::set_default_logger(
		std::make_unique<spdlog::logger>(
			"global"s,
			std::make_shared<spdlog::sinks::basic_file_sink_st>(
				unicode::narrow(path.native()),
				true)));
	spdlog::set_pattern("%^%v%$"s);
	spdlog::set_level(spdlog::level::trace);
}

std::uintptr_t patch_iat(
	win32::module_t* a_module,
	std::uintptr_t a_newFunc,
	std::string_view a_dll,
	std::string_view a_function)
{
	const auto oldFunc = get_iat(a_module, a_dll, a_function);
	const auto original = *reinterpret_cast<std::uintptr_t*>(oldFunc);
	util::safe_write(reinterpret_cast<std::uintptr_t>(oldFunc), a_newFunc);
	return original;
}

namespace hook
{
	inline auto g_dll = "MSVCR110.dll"sv;
	inline auto g_function = "__crtGetShowWindowMode"sv;
	inline int(__cdecl* g_original)(void) = nullptr;

	int __cdecl thunk(void)
	{
		auto dll = win32::load_library(
			win32::get_environment_variable("F4SE_DLL"sv));
		const auto proc =
			reinterpret_cast<void (*)()>(
				win32::get_proc_address(dll.get(), "StartF4SE"sv));
		proc();
		(void)dll.release();  // intentionally leak handle to keep it loaded

		return g_original();
	}
}

// TODO: check thread exit codes
void do_initialize()
{
	const auto mod = win32::get_module_handle(
		win32::get_environment_variable("F4SE_RUNTIME"sv));
	hook::g_original = reinterpret_cast<decltype(hook::g_original)>(
		patch_iat(
			mod,
			reinterpret_cast<std::uintptr_t>(hook::thunk),
			hook::g_dll,
			hook::g_function));
}

int safe_initialize()
{
	const auto cerr = [](std::string_view a_err) {
		unicode::cerr
			<< "failed to initialize log with error:\n"
			<< "\t" << a_err << '\n';
	};

	try {
		initialize_log();
	} catch (const std::exception& a_err) {
		cerr(a_err.what());
		return EXIT_FAILURE;
	} catch (...) {
		cerr("unknown exception"sv);
		return EXIT_FAILURE;
	}

	try {
		do_initialize();
	} catch (const std::exception& a_err) {
		spdlog::error(a_err.what());
		return EXIT_FAILURE;
	} catch (...) {
		spdlog::error("caught unknown exception"sv);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

extern "C" ::INT_PTR __declspec(dllexport) WINAPI Initialize()
{
	if (win32::get_environment_variable("F4SE_WAITFORDEBUGGER"sv) == "1"sv) {
		while (!::IsDebuggerPresent()) {}
	}

	static std::atomic_bool initialized{ false };
	bool expected = false;
	return initialized.compare_exchange_strong(expected, true) ?
               safe_initialize() :
               EXIT_SUCCESS;
}
