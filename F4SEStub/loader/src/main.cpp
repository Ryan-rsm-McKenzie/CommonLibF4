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

	template <class Enum>
	[[nodiscard]] constexpr auto to_underlying(Enum a_val) noexcept  //
		requires(std::is_enum_v<Enum>)
	{
		return static_cast<std::underlying_type_t<Enum>>(a_val);
	}
}

namespace win32
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

namespace cli
{
	namespace detail
	{
		[[nodiscard]] std::wstring normalize(std::wstring_view a_str)
		{
			const auto invoke = [&](wchar_t* a_dst, std::size_t a_len) {
				return ::NormalizeString(
					::NORM_FORM::NormalizationC,
					a_str.data(),
					static_cast<int>(a_str.size()),
					a_dst,
					static_cast<int>(a_len));
			};

			auto len = invoke(nullptr, 0);
			if (len <= 0) {
				win32::error("failed to get normalized string buffer size"sv);
			}

			std::wstring result;
			result.resize(static_cast<std::size_t>(len), L'\0');
			len = invoke(result.data(), result.size() + 1);
			if (len <= 0) {
				win32::error("failed to normalize string"sv);
			}

			result.resize(static_cast<std::size_t>(len), L'\0');
			return result;
		}

		[[nodiscard]] std::wstring to_lower(std::wstring_view a_str)
		{
			const auto invoke = [&](wchar_t* a_dst, std::size_t a_len) {
				return ::LCMapStringEx(
					LOCALE_NAME_SYSTEM_DEFAULT,
					LCMAP_LOWERCASE,
					a_str.data(),
					static_cast<int>(a_str.size()),
					a_dst,
					static_cast<int>(a_len),
					nullptr,
					nullptr,
					0);
			};

			auto len = invoke(nullptr, 0);
			if (len == 0) {
				win32::error("failed to get mapped buffer size"sv);
			}

			std::wstring result;
			result.resize(static_cast<std::size_t>(len), L'\0');
			len = invoke(result.data(), result.size() + 1);
			if (len == 0) {
				win32::error("failed to map string"sv);
			}

			result.resize(static_cast<std::size_t>(len), L'\0');
			return result;
		}

		[[nodiscard]] auto do_parse(std::span<const wchar_t*> a_args)
			-> std::vector<std::string>
		{
			std::vector<std::string> args;
			for (const std::wstring_view arg : a_args.subspan(1)) {
				auto str = normalize(arg);
				if (!arg.empty() && arg.front() == L'-') {
					str = to_lower(str);
				}

				args.push_back(unicode::narrow(str));
			}

			return args;
		}

		struct priority
		{
			bool operator()(const std::string& a_name, const std::string& a_value, DWORD& a_dst)
			{
				constexpr frozen::map<std::string_view, ::DWORD, 6> map = {
					std::make_pair("realtime"sv, REALTIME_PRIORITY_CLASS),
					std::make_pair("high"sv, HIGH_PRIORITY_CLASS),
					std::make_pair("above_normal"sv, ABOVE_NORMAL_PRIORITY_CLASS),
					std::make_pair("normal"sv, NORMAL_PRIORITY_CLASS),
					std::make_pair("below_normal"sv, BELOW_NORMAL_PRIORITY_CLASS),
					std::make_pair("idle"sv, IDLE_PRIORITY_CLASS)
				};

				const auto value = [](std::string_view a_str) {
					const auto str = unicode::widen(a_str);
					const auto lower = to_lower(str);
					return unicode::narrow(lower);
				}(a_value);

				const auto it = map.find(value);
				if (it != map.end()) {
					a_dst = it->second;
					return true;
				} else {
					throw args::ParseError(
						fmt::format(
							FMT_STRING("Argument \'{}\' received invalid value type \'{}\'"),
							a_name,
							a_value));
				}
			}
		};
	}

	struct options
	{
		std::optional<std::string> altdll;
		std::optional<std::string> altexe;

		std::optional<::DWORD> affinity;
		std::optional<::DWORD> priority;

		bool editor{ false };
		bool forcesteamloader{ false };
		bool launchsteam{ false };
		bool minfo{ false };
		bool noskiplauncher{ false };
		bool notimeout{ false };
		bool verbose{ false };
		bool waitforclose{ false };
		bool waitfordebugger{ false };
	};

	[[nodiscard]] auto parse(std::span<const wchar_t*> a_args)
		-> std::optional<options>
	{
		args::ArgumentParser p{ "USAGE: f4se_loader.exe [options]"s };
		p.helpParams.descriptionindent = 0;
		p.helpParams.helpindent = 30;
		p.helpParams.progindent = 0;
		p.helpParams.showProglineOptions = false;
		p.Prog("OVERVIEW: F4SE DLL Loader"s);
		p.LongPrefix("-"s);

		args::HelpFlag help{ p, ""s, "print this options list"s, { 'h', "help"s } };

		args::ValueFlag<::DWORD> affinity{ p, "mask"s, "set the processor affinity mask"s, { "affinity"s } };
		args::ValueFlag<std::string> altdll{ p, "altdll"s, "set alternate dll path"s, { "altdll"s } };
		args::ValueFlag<std::string> altexe{ p, "path"s, "set alternate exe path"s, { "altexe"s } };
		args::Flag editor{ p, ""s, "launch the creation kit"s, { "editor"s } };
		args::Flag forcesteamloader{ p, ""s, "override exe type detection and use steam loader"s, { "forcesteamloader"s } };
		args::Flag launchsteam{ p, ""s, "attempt to launch steam if it is not running"s, { "launchsteam"s } };
		args::Flag minfo{ p, ""s, "log information about the DLLs loaded in to the target process"s, { "minfo"s } };
		args::Flag noskiplauncher{ p, ""s, "does not skip the default Bethesda launcher window (this option may cause compatibility problems)"s, { "noskiplauncher"s } };
		args::Flag notimeout{ p, ""s, "don't automatically terminate the process if the proxy takes too long"s, { "notimeout"s } };
		args::ValueFlag<::DWORD, detail::priority> priority{ p, "level"s, "set the launched program\'s priority"s, { "priority"s } };
		args::Flag verbose{ p, ""s, "print verbose messages to the console"s, { 'v', "verbose"s } };
		args::Flag waitforclose{ p, ""s, "wait for the launched program to close"s, { "waitforclose"s } };
		args::Flag waitfordebugger{ p, ""s, "wait for a debugger to attach before proceeding"s, { "waitfordebugger"s } };

		try {
			const auto args = detail::do_parse(a_args);
			p.ParseArgs(args.begin(), args.end());
		} catch (const args::Help&) {
			spdlog::trace(p);
			return std::nullopt;
		} catch (const args::ParseError& a_err) {
			spdlog::error(a_err.what());
			spdlog::trace(""sv);
			spdlog::trace(p);
			return std::nullopt;
		}

		const auto setIf = [](auto& a_option, auto& a_flag) {
			if (a_flag.Matched()) {
				a_option = a_flag.Get();
			}
		};

		options o;
#define SET_IF(a_option) setIf(o.a_option, a_option)
		SET_IF(affinity);
		SET_IF(altdll);
		SET_IF(altexe);
		SET_IF(editor);
		SET_IF(forcesteamloader);
		SET_IF(launchsteam);
		SET_IF(minfo);
		SET_IF(noskiplauncher);
		SET_IF(notimeout);
		SET_IF(priority);
		SET_IF(verbose);
		SET_IF(waitforclose);
		SET_IF(waitfordebugger);
#undef SET_IF

		return o;
	}
}

namespace win32
{
	namespace detail
	{
		template <class Deleter>
		class unique_struct
		{
		public:
			using deleter_type = Deleter;
			using value_type = typename deleter_type::value_type;

			static_assert(std::invocable<deleter_type, value_type&>);

			unique_struct() noexcept { zero(); }
			~unique_struct() noexcept { destroy(); }

			unique_struct(unique_struct&& a_rhs) noexcept :
				_value(a_rhs._value)
			{
				a_rhs.zero();
			}

			unique_struct& operator=(unique_struct&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					destroy();
					_value = a_rhs._value;
					a_rhs.zero();
				}
				return *this;
			}

			unique_struct(const unique_struct&) = delete;
			unique_struct& operator=(const unique_struct&) = delete;

			[[nodiscard]] value_type* get() noexcept { return std::addressof(_value); }
			[[nodiscard]] const value_type* get() const noexcept { return std::addressof(_value); }

			[[nodiscard]] value_type* operator->() noexcept { return get(); }
			[[nodiscard]] const value_type* operator->() const noexcept { return get(); }

			[[nodiscard]] value_type& operator*() noexcept { return *get(); }
			[[nodiscard]] const value_type& operator*() const noexcept { return *get(); }

		private:
			void destroy() noexcept
			{
				deleter_type()(_value);
				zero();
			}

			void zero() noexcept { ZeroMemory(get(), sizeof(value_type)); }

			value_type _value{};
		};

		void close_handle(::HANDLE a_handle)
		{
			if (a_handle && !::CloseHandle(a_handle)) {
				win32::error("failed to close handle"sv);
			}
		}

		struct delete_startup_info
		{
			using value_type = ::STARTUPINFOW;

			void operator()(::STARTUPINFOW& a_info)
			{
				close_handle(a_info.hStdInput);
				close_handle(a_info.hStdOutput);
				close_handle(a_info.hStdOutput);
			}
		};

		struct delete_process_information
		{
			using value_type = ::PROCESS_INFORMATION;

			void operator()(value_type& a_info)
			{
				close_handle(a_info.hProcess);
				close_handle(a_info.hThread);
			}
		};
	}

	using unique_startup_info = detail::unique_struct<detail::delete_startup_info>;
	using unique_process_information = detail::unique_struct<detail::delete_process_information>;

	struct module_t;
	struct thread_t;

	using proc_t = void();

	namespace detail
	{
		struct close_module_handle
		{
			void operator()(module_t* a_module)
			{
				close_handle(reinterpret_cast<::HANDLE>(a_module));
			}
		};

		struct close_thread_handle
		{
			void operator()(thread_t* a_thread)
			{
				close_handle(reinterpret_cast<::HANDLE>(a_thread));
			}
		};
	}

	using unique_module = std::unique_ptr<module_t, detail::close_module_handle>;
	using unique_thread = std::unique_ptr<thread_t, detail::close_thread_handle>;

	/*
	* @pre a_proc is a valid process
	* @pre a_prio is a valid priority or nullopt
	* @post results are NOT null
	*/
	[[nodiscard]] auto create_process(
		std::string_view a_proc,
		std::optional<::DWORD> a_prio)
		-> std::pair<unique_module, unique_thread>
	{
		const auto proc = unicode::widen(a_proc.data(), a_proc.size());
		unique_process_information pi;
		unique_startup_info si;
		si->cb = sizeof(decltype(si)::value_type);

		const auto success = ::CreateProcessW(
			proc.c_str(),
			nullptr,
			nullptr,
			nullptr,
			false,
			a_prio.value_or(0) | CREATE_SUSPENDED,
			nullptr,
			nullptr,
			si.get(),
			pi.get());

		if (!success || !pi->hProcess || !pi->hThread) {
			win32::error("failed to create process"sv);
		} else {
			unique_module mod{ reinterpret_cast<module_t*>(std::exchange(pi->hProcess, nullptr)) };
			unique_thread thread{ reinterpret_cast<thread_t*>(std::exchange(pi->hThread, nullptr)) };
			return { std::move(mod), std::move(thread) };
		}
	}

	/*
	* @pre a_module is NOT null
	* @pre a_start is NOT null
	* @post result is NOT null
	*/
	[[nodiscard]] auto create_remote_thread(
		module_t* a_module,
		std::uint32_t (*a_start)(void*),
		void* a_parameter)
		-> unique_thread
	{
		assert(a_module != nullptr);
		assert(a_start != nullptr);

		const auto thread = ::CreateRemoteThread(
			reinterpret_cast<::HANDLE>(a_module),
			nullptr,
			0,
			reinterpret_cast<::LPTHREAD_START_ROUTINE>(a_start),
			a_parameter,
			0,
			nullptr);

		if (!thread) {
			win32::error("failed to create remote thread"sv);
		} else {
			return unique_thread{ reinterpret_cast<thread_t*>(thread) };
		}
	}

	/*
	* @pre a_module is NOT null
	*/
	void flush_instruction_cache(module_t* a_module)
	{
		assert(a_module != nullptr);

		if (::FlushInstructionCache(
				a_module,
				nullptr,
				0) == 0) {
			win32::error("failed to flush instruction cache"sv);
		}
	}

	[[nodiscard]] auto get_file_version(std::string_view a_file)
		-> std::array<std::string, 4>
	{
		const auto file = unicode::widen(a_file);

		::DWORD handle = 0;
		const auto bufLen = ::GetFileVersionInfoSizeW(file.c_str(), &handle);
		if (bufLen == 0) {
			win32::error("failed to get file version info size"sv);
		}

		std::vector<std::byte> buf(static_cast<std::size_t>(bufLen), std::byte{ 0 });
		if (::GetFileVersionInfoW(
				file.c_str(),
				handle,
				static_cast<::DWORD>(buf.size()),
				buf.data()) == 0) {
			win32::error("failed to get file version info"sv);
		}

		void* verBuf = nullptr;
		::UINT verLen = 0;
		if (::VerQueryValueW(
				buf.data(),
				L"\\StringFileInfo\\040904B0\\ProductVersion",
				&verBuf,
				&verLen) == 0) {
			win32::error("failed to query version value"sv);
		}

		std::array<std::string, 4> result;
		const auto version = unicode::narrow(
			static_cast<const wchar_t*>(verBuf),
			static_cast<std::size_t>(verLen - 1));
		std::regex pattern{ R"((\d+)\.(\d+)\.(\d+)\.(\d+))"s, std::regex_constants::ECMAScript };
		std::smatch matches;
		if (std::regex_match(version, matches, pattern) && matches.size() == result.size() + 1) {
			for (std::size_t i = 0; i < result.size(); ++i) {
				const auto& match = matches[i + 1];
				result[i].assign(match.first, match.second);
			}
		} else {
			assert(false);
		}

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
			win32::error("failed to get module handle"sv);
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
			win32::error("failed to get proc address"sv);
		} else {
			return reinterpret_cast<proc_t*>(proc);
		}
	}

	/*
	* @pre a_thread is NOT null
	*/
	void resume_thread(
		thread_t* a_thread)
	{
		assert(a_thread != nullptr);
		if (::ResumeThread(
				reinterpret_cast<::HANDLE>(a_thread)) ==
			static_cast<::DWORD>(-1)) {
			win32::error("failed to resume thread"sv);
		}
	}

	void set_environment_variable(
		std::string_view a_name,
		std::string_view a_value)
	{
		const auto name = unicode::widen(a_name);
		const auto value = unicode::widen(a_value);
		if (::SetEnvironmentVariableW(
				name.c_str(),
				value.c_str()) == 0) {
			win32::error("failed to set environment variable"sv);
		}
	}

	/*
	* @pre a_module is NOT null
	*/
	void terminate_process(
		module_t* a_module,
		int a_exitCode)
	{
		assert(a_module != nullptr);

		if (::TerminateProcess(
				reinterpret_cast<::HANDLE>(a_module),
				static_cast<::UINT>(a_exitCode)) == 0) {
			win32::error("failed to terminate process"sv);
		}
	}

	/*
	* @pre a_module is NOT null
	* @pre a_size > 0
	* @post result is NOT null
	*/
	[[nodiscard]] auto virtual_alloc(
		module_t* a_module,
		std::size_t a_size)
	{
		assert(a_module != nullptr);
		assert(a_size > 0);

		const auto mem = ::VirtualAllocEx(  // TODO: FlushInstructionCache
			reinterpret_cast<::HANDLE>(a_module),
			nullptr,
			a_size,
			MEM_COMMIT,
			PAGE_EXECUTE_READWRITE);

		if (!mem) {
			win32::error("failed to virtual allocate"sv);
		} else {
			const auto free = [=](std::byte* a_memory) {
				if (a_memory &&
					!::VirtualFreeEx(
						reinterpret_cast<::HANDLE>(a_module),
						a_memory,
						0,
						MEM_RELEASE)) {
					win32::error("failed to free virtual memory"sv);
				}
			};

			return std::unique_ptr<std::byte, decltype(free)>{
				static_cast<std::byte*>(mem),
				free
			};
		}
	}

	/*
	* @pre a_thread is NOT null
	*/
	void wait_for_single_object(
		thread_t* a_thread,
		std::chrono::milliseconds a_time)
	{
		assert(a_thread != nullptr);

		const ::DWORD time =
			a_time == std::chrono::milliseconds::max() ?
                INFINITE :
                static_cast<::DWORD>(a_time.count());

		if (::WaitForSingleObject(
				reinterpret_cast<::HANDLE>(a_thread),
				time) != WAIT_OBJECT_0) {
			win32::error("failed to wait for single object"sv);
		}
	}

	/*
	* @pre a_module is NOT null
	* @pre a_dst is NOT null
	* @pre a_src is NOT empty
	*/
	void write_process_memory(
		module_t* a_module,
		std::byte* a_dst,
		std::span<const std::byte> a_src)
	{
		assert(a_module != nullptr);
		assert(a_dst != nullptr);
		assert(!a_src.empty());

		::SIZE_T written = 0;
		if (!::WriteProcessMemory(
				reinterpret_cast<::HANDLE>(a_module),
				a_dst,
				a_src.data(),
				a_src.size(),
				&written) ||
			written != a_src.size()) {
			win32::error("failed to write process memory"sv);
		}
	}
}

namespace detail
{
	struct args_t
	{
		::HMODULE (*loadLibraryW)(::LPCWSTR){ nullptr };  // LoadLibraryW
		::LPCWSTR libFileName{ nullptr };                 // LoadLibraryW -> rcx

		::FARPROC (*getProcAddress)(::HMODULE, ::LPCSTR){ nullptr };  // GetProcAddress
		::LPCSTR procName{ nullptr };                                 // GetProcAddress -> rdx
	};

	struct patch_t :
		Xbyak::CodeGenerator
	{
		// MUST VERIFY ANY CHANGES BY HAND
		// https://godbolt.org/z/484fqa
		patch_t()
		{
			Xbyak::Label LN3;
			Xbyak::Label LN6;

			push(rbx);
			sub(rsp, 0x20);
			mov(rbx, rcx);  // rcx == args_t*

			mov(rcx, ptr[rcx + offsetof(args_t, libFileName)]);
			call(ptr[rbx]);

			test(rax, rax);
			je(LN6);

			mov(rdx, ptr[rbx + offsetof(args_t, procName)]);
			test(rdx, rdx);
			je(LN3);

			mov(rcx, rax);
			call(ptr[rbx + offsetof(args_t, getProcAddress)]);

			test(rax, rax);
			je(LN6);

			call(rax);

			L(LN3);
			xor_(eax, eax);
			add(rsp, 0x20);
			pop(rbx);
			ret(0);

			L(LN6);
			mov(eax, 1);
			add(rsp, 0x20);
			pop(rbx);
			ret(0);
		}
	};

	enum class type_t : std::size_t
	{
		kCode,
		kArgs,
		kLibFileName,
		kProcName,

		kTotal
	};

	class offset_calculator
	{
	public:
		[[nodiscard]] std::size_t offset_of(type_t a_type) const noexcept
		{
			return std::accumulate(
				_impl.begin(),
				_impl.begin() + stl::to_underlying(a_type),
				std::size_t{ 0 },
				[](std::size_t a_current, const value_type& a_val) {
					return a_current + a_val.rounded;
				});
		}

		void set(type_t a_type, std::size_t a_size) noexcept
		{
			_impl[stl::to_underlying(a_type)] =
				value_type{
					a_size,
					std::max<std::size_t>(
						std::bit_ceil(a_size + 1),
						0x10)
				};
		}

		[[nodiscard]] std::size_t size_of(type_t a_type) const noexcept
		{
			return _impl[stl::to_underlying(a_type)].real;
		}

		[[nodiscard]] std::size_t total_size() const noexcept { return offset_of(type_t::kTotal); }

	private:
		struct value_type
		{
			std::size_t real{ 0 };
			std::size_t rounded{ 0 };
		};

		std::array<
			value_type,
			stl::to_underlying(type_t::kTotal)>
			_impl;
	};
}

void augment_environment(
	std::string_view a_runtime,
	std::string_view a_dll,
	bool a_waitForDebugger)
{
	win32::set_environment_variable("F4SE_DLL"sv, a_dll);
	win32::set_environment_variable("F4SE_RUNTIME"sv, a_runtime);
	win32::set_environment_variable("F4SE_WAITFORDEBUGGER"sv, (a_waitForDebugger ? "1"sv : "0"sv));
}

[[nodiscard]] auto get_runtime_names(const cli::options& a_options)
	-> std::pair<std::string, std::string>  // exe, dll
{
	auto exe =
		a_options.altexe ?
            *a_options.altexe :
		a_options.editor ?
            "CreationKit.exe"s :
            "Fallout4.exe"s;
	auto dll = [&]() {
		if (a_options.altdll) {
			return *a_options.altdll;
		} else {
			const auto version = win32::get_file_version(exe);
			return fmt::format(
				FMT_STRING("{}_{}_{}_{}.dll"),
				(a_options.editor ?
                        "f4se_editor"s :
                        "f4se"s),
				version[0],
				version[1],
				version[2]);
		}
	}();

	const auto error = [](std::string_view a_file) {
		throw std::runtime_error(
			fmt::format(
				FMT_STRING("file does not exist: {}"),
				a_file));
	};
	if (!std::filesystem::exists(exe)) {
		error(exe);
	} else if (!std::filesystem::exists(dll)) {
		error(dll);
	}

	return { std::move(exe), std::move(dll) };
}

void initialize_log()
{
	spdlog::set_default_logger(
		std::make_unique<spdlog::logger>(
			"global"s,
			std::make_unique<spdlog::sinks::stdout_color_sink_st>()));
	spdlog::set_pattern("%^%v%$"s);
	spdlog::set_level(spdlog::level::trace);
}

[[nodiscard]] auto prepare_cave(
	win32::module_t* a_module,
	std::string_view a_dll,
	std::string a_init)
{
	assert(a_module != nullptr);
	using type_t = detail::type_t;

	detail::patch_t code;
	code.ready();

	const auto kernel = win32::get_module_handle("Kernel32.dll"sv);
	detail::args_t args;
	args.loadLibraryW = reinterpret_cast<decltype(&::LoadLibraryW)>(
		win32::get_proc_address(kernel, "LoadLibraryW"sv));
	args.getProcAddress = reinterpret_cast<decltype(&::GetProcAddress)>(
		win32::get_proc_address(kernel, "GetProcAddress"sv));

	const auto dll = unicode::widen(a_dll);

	detail::offset_calculator calc;
	calc.set(type_t::kCode, code.getSize());
	calc.set(type_t::kArgs, sizeof(args));
	calc.set(type_t::kLibFileName, (dll.size() + 1) * sizeof(decltype(dll)::value_type));
	calc.set(type_t::kProcName, (a_init.size() + 1) * sizeof(decltype(a_init)::value_type));

	std::vector<std::byte> patch(
		calc.total_size(),
		std::byte{ 0xCC });
	auto mem = win32::virtual_alloc(
		a_module,
		patch.size());

	args.libFileName = reinterpret_cast<::LPCWSTR>(mem.get() + calc.offset_of(type_t::kLibFileName));
	args.procName = !a_init.empty() ?
                        reinterpret_cast<::LPCSTR>(mem.get() + calc.offset_of(type_t::kProcName)) :
                        nullptr;

	const auto write = [&](type_t a_type, const void* a_src) {
		std::memcpy(
			patch.data() + calc.offset_of(a_type),
			a_src,
			calc.size_of(a_type));
	};

	write(type_t::kCode, code.getCode());
	write(type_t::kArgs, &args);
	write(type_t::kLibFileName, dll.c_str());
	write(type_t::kProcName, a_init.c_str());

	win32::write_process_memory(
		a_module,
		mem.get(),
		std::span{ patch.begin(), patch.end() });
	win32::flush_instruction_cache(a_module);

	return std::make_pair(
		std::move(mem),
		mem.get() + calc.offset_of(type_t::kArgs));
}

// TODO: check thread/proc exit codes
void do_main(std::span<const wchar_t*> a_args)
{
	const auto options = cli::parse(a_args);
	if (!options) {
		return;
	}

	const auto [exeName, dllName] = get_runtime_names(*options);
	augment_environment(exeName, dllName, options->waitfordebugger);

	const auto [proc, procThread] = win32::create_process(exeName, options->priority);
	stl::scope_exit terminator([&]() { win32::terminate_process(proc.get(), EXIT_FAILURE); });

	const auto [cave, context] = prepare_cave(
		proc.get(),
		(options->forcesteamloader ? "f4se_steam_loader.dll"sv : dllName),
		(options->forcesteamloader ? "Initialize"s : "StartF4SE"s));
	const auto proxyThread = win32::create_remote_thread(
		proc.get(),
		reinterpret_cast<std::uint32_t (*)(void*)>(cave.get()),
		context);
	win32::wait_for_single_object(
		proxyThread.get(),
		options->notimeout ? std::chrono::milliseconds::max() : 1min);

	win32::resume_thread(procThread.get());
	terminator.release();
	if (options->waitforclose) {
		win32::wait_for_single_object(
			procThread.get(),
			std::chrono::milliseconds::max());
	}
}

int wmain(int a_argc, wchar_t* a_argv[])
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
		do_main({ const_cast<const wchar_t**>(a_argv), static_cast<std::size_t>(a_argc) });
	} catch (const std::exception& a_err) {
		spdlog::error(a_err.what());
		return EXIT_FAILURE;
	} catch (...) {
		spdlog::error("caught unknown exception"sv);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
