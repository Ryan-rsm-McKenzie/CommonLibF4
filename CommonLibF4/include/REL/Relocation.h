#pragma once

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_nopropQual, a_propQual, ...)              \
	template <                                                                                    \
		class R,                                                                                  \
		class Cls,                                                                                \
		class... Args>                                                                            \
	struct member_function_pod_type<R (Cls::*)(Args...) __VA_ARGS__ a_nopropQual a_propQual>      \
	{                                                                                             \
		using type = R(__VA_ARGS__ Cls*, Args...) a_propQual;                                     \
	};                                                                                            \
                                                                                                  \
	template <                                                                                    \
		class R,                                                                                  \
		class Cls,                                                                                \
		class... Args>                                                                            \
	struct member_function_pod_type<R (Cls::*)(Args..., ...) __VA_ARGS__ a_nopropQual a_propQual> \
	{                                                                                             \
		using type = R(__VA_ARGS__ Cls*, Args..., ...) a_propQual;                                \
	};

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(a_qualifer, ...)              \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_qualifer, , ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL(a_qualifer, noexcept, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_POD_TYPE(...)                 \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(, __VA_ARGS__)    \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(&, ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER(&&, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_nopropQual, a_propQual, ...)              \
	template <                                                                                        \
		class R,                                                                                      \
		class Cls,                                                                                    \
		class... Args>                                                                                \
	struct member_function_non_pod_type<R (Cls::*)(Args...) __VA_ARGS__ a_nopropQual a_propQual>      \
	{                                                                                                 \
		using type = R&(__VA_ARGS__ Cls*, void*, Args...)a_propQual;                                  \
	};                                                                                                \
                                                                                                      \
	template <                                                                                        \
		class R,                                                                                      \
		class Cls,                                                                                    \
		class... Args>                                                                                \
	struct member_function_non_pod_type<R (Cls::*)(Args..., ...) __VA_ARGS__ a_nopropQual a_propQual> \
	{                                                                                                 \
		using type = R&(__VA_ARGS__ Cls*, void*, Args..., ...)a_propQual;                             \
	};

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(a_qualifer, ...)              \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_qualifer, , ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL(a_qualifer, noexcept, ##__VA_ARGS__)

#define REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(...)                 \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(, __VA_ARGS__)    \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(&, ##__VA_ARGS__) \
	REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER(&&, ##__VA_ARGS__)

namespace REL
{
	class ID;
	class IDManager;
	class Module;
	class Offset;
	class Segment;
	class Version;

	template <class>
	class Relocation;

	namespace detail
	{
		template <class>
		struct member_function_pod_type;

		REL_MAKE_MEMBER_FUNCTION_POD_TYPE();
		REL_MAKE_MEMBER_FUNCTION_POD_TYPE(const);
		REL_MAKE_MEMBER_FUNCTION_POD_TYPE(volatile);
		REL_MAKE_MEMBER_FUNCTION_POD_TYPE(const volatile);

		template <class F>
		using member_function_pod_type_t = typename member_function_pod_type<F>::type;

		template <class>
		struct member_function_non_pod_type;

		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE();
		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(const);
		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(volatile);
		REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE(const volatile);

		template <class F>
		using member_function_non_pod_type_t = typename member_function_non_pod_type<F>::type;

		// https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention

		template <class T>
		struct meets_length_req :
			std::disjunction<
				std::bool_constant<sizeof(T) == 1>,
				std::bool_constant<sizeof(T) == 2>,
				std::bool_constant<sizeof(T) == 4>,
				std::bool_constant<sizeof(T) == 8>>
		{};

		template <class T>
		struct meets_function_req :
			std::conjunction<
				std::is_trivially_constructible<T>,
				std::is_trivially_destructible<T>,
				std::is_trivially_copy_assignable<T>,
				std::negation<
					std::is_polymorphic<T>>>
		{};

		template <class T>
		struct meets_member_req :
			std::is_standard_layout<T>
		{};

		template <class T, class = void>
		struct is_x64_pod :
			std::true_type
		{};

		template <class T>
		struct is_x64_pod<
			T,
			std::enable_if_t<
				std::is_union_v<T>>> :
			std::false_type
		{};

		template <class T>
		struct is_x64_pod<
			T,
			std::enable_if_t<
				std::is_class_v<T>>> :
			std::conjunction<
				meets_length_req<T>,
				meets_function_req<T>,
				meets_member_req<T>>
		{};

		template <class T>
		inline constexpr bool is_x64_pod_v = is_x64_pod<T>::value;

		template <
			class F,
			class First,
			class... Rest>
		decltype(auto) invoke_member_function_non_pod(F&& a_func, First&& a_first, Rest&&... a_rest) noexcept(
			std::is_nothrow_invocable_v<F, First, Rest...>)
		{
			using result_t = std::invoke_result_t<F, First, Rest...>;
			std::aligned_storage_t<sizeof(result_t), alignof(result_t)> result;

			using func_t = member_function_non_pod_type_t<F>;
			auto func = unrestricted_cast<func_t*>(std::forward<F>(a_func));

			return func(std::forward<First>(a_first), std::addressof(result), std::forward<Rest>(a_rest)...);
		}
	}

	template <
		class F,
		class... Args,
		std::enable_if_t<
			std::is_invocable_v<F, Args...>,
			int> = 0>
	std::invoke_result_t<F, Args...> invoke(F&& a_func, Args&&... a_args) noexcept(
		std::is_nothrow_invocable<F, Args...>)
	{
		if constexpr (std::is_member_function_pointer_v<std::decay_t<F>>) {
			if constexpr (detail::is_x64_pod_v<std::invoke_result_t<F, Args...>>) {	 // member functions == free functions in x64
				using func_t = detail::member_function_pod_type_t<std::decay_t<F>>;
				auto func = unrestricted_cast<func_t*>(std::forward<F>(a_func));
				return func(std::forward<Args>(a_args)...);
			} else {  // shift args to insert result
				return detail::invoke_member_function_non_pod(std::forward<F>(a_func), std::forward<Args>(a_args)...);
			}
		} else {
			return std::forward<F>(a_func)(std::forward<Args>(a_args)...);
		}
	}

	inline void safe_write(std::uintptr_t a_dst, const void* a_src, std::size_t a_count)
	{
		std::uint32_t old{ 0 };
		auto success =
			WinAPI::VirtualProtect(
				reinterpret_cast<void*>(a_dst),
				a_count,
				(WinAPI::PAGE_EXECUTE_READWRITE),
				std::addressof(old));
		if (success != 0) {
			std::memcpy(reinterpret_cast<void*>(a_dst), a_src, a_count);
			success =
				WinAPI::VirtualProtect(
					reinterpret_cast<void*>(a_dst),
					a_count,
					old,
					std::addressof(old));
		}

		assert(success != 0);
	}

	template <class T>
	void safe_write(std::uintptr_t a_dst, const T& a_data)
	{
		safe_write(a_dst, std::addressof(a_data), sizeof(T));
	}

	template <class T>
	void safe_write(std::uintptr_t a_dst, stl::span<T> a_data)
	{
		safe_write(a_dst, a_data.data(), a_data.size_bytes());
	}

	class Version
	{
	public:
		using value_type = std::uint16_t;
		using reference = value_type&;
		using const_reference = const value_type&;

		constexpr Version() noexcept = default;

		constexpr Version(std::array<value_type, 4> a_version) noexcept :
			_impl(a_version)
		{}

		constexpr Version(value_type a_v1, value_type a_v2, value_type a_v3, value_type a_v4) noexcept :
			_impl{ a_v1, a_v2, a_v3, a_v4 }
		{}

		[[nodiscard]] constexpr reference operator[](std::size_t a_idx) noexcept { return _impl[a_idx]; }
		[[nodiscard]] constexpr const_reference operator[](std::size_t a_idx) const noexcept { return _impl[a_idx]; }

		[[nodiscard]] int constexpr compare(const Version& a_rhs) const noexcept
		{
			for (std::size_t i = 0; i < _impl.size(); ++i) {
				if ((*this)[i] != a_rhs[i]) {
					return (*this)[i] < a_rhs[i] ? -1 : 1;
				}
			}
			return 0;
		}

		[[nodiscard]] std::string string() const
		{
			std::string result;
			for (std::size_t i = 0; i < _impl.size(); ++i) {
				result += std::to_string(_impl[i]);
				result += '-';
			}
			result.pop_back();
			return result;
		}

		[[nodiscard]] std::wstring wstring() const
		{
			std::wstring result;
			for (std::size_t i = 0; i < _impl.size(); ++i) {
				result += std::to_wstring(_impl[i]);
				result += L'-';
			}
			result.pop_back();
			return result;
		}

	private:
		std::array<value_type, 4> _impl{ 0, 0, 0, 0 };
	};

	[[nodiscard]] constexpr bool operator==(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) == 0; }
	[[nodiscard]] constexpr bool operator!=(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) != 0; }
	[[nodiscard]] constexpr bool operator<(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) < 0; }
	[[nodiscard]] constexpr bool operator<=(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) <= 0; }
	[[nodiscard]] constexpr bool operator>(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) > 0; }
	[[nodiscard]] constexpr bool operator>=(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) >= 0; }

	class Segment
	{
	public:
		enum Name : std::size_t
		{
			text,
			interpr,
			idata,
			rdata,
			data,
			pdata,
			tls,
			total
		};

		constexpr Segment() noexcept = default;

		constexpr Segment(std::uintptr_t a_proxyBase, std::uintptr_t a_address, std::uintptr_t a_size) noexcept :
			_proxyBase(a_proxyBase),
			_address(a_address),
			_size(a_size)
		{}

		[[nodiscard]] constexpr std::uintptr_t address() const noexcept { return _address; }
		[[nodiscard]] constexpr std::size_t offset() const noexcept { return address() - _proxyBase; }
		[[nodiscard]] constexpr std::size_t size() const noexcept { return _size; }

		[[nodiscard]] void* pointer() const noexcept { return reinterpret_cast<void*>(address()); }

		template <class T>
		[[nodiscard]] T* pointer() const noexcept
		{
			return static_cast<T*>(pointer());
		}

	private:
		std::uintptr_t _proxyBase{ 0 };
		std::uintptr_t _address{ 0 };
		std::size_t _size{ 0 };
	};

	class Module
	{
	public:
		[[nodiscard]] static Module& get()
		{
			static Module singleton;
			return singleton;
		}

		[[nodiscard]] constexpr std::uintptr_t base() const noexcept { return _base; }
		[[nodiscard]] constexpr Version version() const noexcept { return _version; }

		[[nodiscard]] constexpr Segment segment(Segment::Name a_segment) const noexcept { return _segments[a_segment]; }

		[[nodiscard]] void* pointer() const noexcept { return reinterpret_cast<void*>(base()); }

		template <class T>
		[[nodiscard]] T* pointer() const noexcept
		{
			return static_cast<T*>(pointer());
		}

	private:
		Module() { load(); }

		Module(const Module&) = delete;
		Module(Module&&) = delete;

		~Module() noexcept = default;

		Module& operator=(const Module&) = delete;
		Module& operator=(Module&&) = delete;

		void load()
		{
			auto handle = WinAPI::GetModuleHandle(FILENAME.data());
			if (handle == nullptr) {
				stl::report_and_fail("failed to obtain module handle"sv);
			}
			_base = reinterpret_cast<std::uintptr_t>(handle);
			_natvis = _base;

			load_version();
			load_segments();
		}

		void load_segments();

		void load_version()
		{
			std::uint32_t dummy;
			std::vector<char> buf(WinAPI::GetFileVersionInfoSize(FILENAME.data(), std::addressof(dummy)));
			if (buf.size() == 0) {
				stl::report_and_fail("failed to obtain file version info size"sv);
			}

			if (!WinAPI::GetFileVersionInfo(FILENAME.data(), 0, static_cast<std::uint32_t>(buf.size()), buf.data())) {
				stl::report_and_fail("failed to obtain file version info"sv);
			}

			void* verBuf{ nullptr };
			std::uint32_t verLen{ 0 };
			if (!WinAPI::VerQueryValue(buf.data(), L"\\StringFileInfo\\040904B0\\ProductVersion", std::addressof(verBuf), std::addressof(verLen))) {
				stl::report_and_fail("failed to query value"sv);
			}

			std::wistringstream ss(
				std::wstring(static_cast<const wchar_t*>(verBuf), verLen));
			std::wstring token;
			for (std::size_t i = 0; i < 4 && std::getline(ss, token, L'.'); ++i) {
				_version[i] = static_cast<std::uint16_t>(std::stoi(token));
			}
		}

		static constexpr auto FILENAME = L"Fallout4.exe"sv;

		static constexpr std::array SEGMENTS{
			".text"sv,
			".interpr"sv,
			".idata"sv,
			".rdata"sv,
			".data"sv,
			".pdata"sv,
			".tls"sv
		};

		static inline std::uintptr_t _natvis{ 0 };

		std::array<Segment, Segment::total> _segments;
		Version _version;
		std::uintptr_t _base{ 0 };
	};

	class IDDatabase
	{
	private:
		struct mapping_t
		{
			std::uint64_t id;
			std::uint64_t offset;
		};

	public:
		class Offset2ID
		{
		public:
			using value_type = mapping_t;
			using container_type = std::vector<value_type>;
			using size_type = typename container_type::size_type;
			using const_iterator = typename container_type::const_iterator;
			using const_reverse_iterator = typename container_type::const_reverse_iterator;

			template <
				class ExecutionPolicy,
				std::enable_if_t<
					std::is_execution_policy_v<
						stl::remove_cvref_t<ExecutionPolicy>>,
					int> = 0>
			Offset2ID(ExecutionPolicy&& a_policy)
			{
				const auto id2offset = IDDatabase::get().get_id2offset();
				_offset2id.reserve(id2offset.size());
				_offset2id.insert(_offset2id.begin(), id2offset.begin(), id2offset.end());
				std::sort(
					a_policy,
					_offset2id.begin(),
					_offset2id.end(),
					[](auto&& a_lhs, auto&& a_rhs) {
						return a_lhs.offset < a_rhs.offset;
					});
			}

			Offset2ID() :
				Offset2ID(std::execution::sequenced_policy{})
			{}

			[[nodiscard]] std::uint64_t operator()(std::size_t a_offset) const
			{
				if (_offset2id.empty()) {
					stl::report_and_fail("data is empty"sv);
				}

				const mapping_t elem{ 0, a_offset };
				const auto it = std::lower_bound(
					_offset2id.begin(),
					_offset2id.end(),
					elem,
					[](auto&& a_lhs, auto&& a_rhs) {
						return a_lhs.offset < a_rhs.offset;
					});
				if (it == _offset2id.end()) {
					stl::report_and_fail("offset not found"sv);
				}

				return it->id;
			}

			[[nodiscard]] const_iterator begin() const noexcept { return _offset2id.begin(); }
			[[nodiscard]] const_iterator cbegin() const noexcept { return _offset2id.cbegin(); }

			[[nodiscard]] const_iterator end() const noexcept { return _offset2id.end(); }
			[[nodiscard]] const_iterator cend() const noexcept { return _offset2id.cend(); }

			[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return _offset2id.rbegin(); }
			[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return _offset2id.crbegin(); }

			[[nodiscard]] const_reverse_iterator rend() const noexcept { return _offset2id.rend(); }
			[[nodiscard]] const_reverse_iterator crend() const noexcept { return _offset2id.crend(); }

			[[nodiscard]] size_type size() const noexcept { return _offset2id.size(); }

		private:
			container_type _offset2id;
		};

		[[nodiscard]] static IDDatabase& get()
		{
			static IDDatabase singleton;
			return singleton;
		}

		[[nodiscard]] std::size_t id2offset(std::uint64_t a_id) const
		{
			if (_id2offset.empty()) {
				stl::report_and_fail("data is empty"sv);
			}

			const mapping_t elem{ a_id, 0 };
			const auto it = std::lower_bound(
				_id2offset.begin(),
				_id2offset.end(),
				elem,
				[](auto&& a_lhs, auto&& a_rhs) {
					return a_lhs.id < a_rhs.id;
				});
			if (it == _id2offset.end()) {
				stl::report_and_fail("id not found"sv);
			}

			return static_cast<std::size_t>(it->offset);
		}

	protected:
		friend class Offset2ID;

		[[nodiscard]] stl::span<const mapping_t> get_id2offset() const noexcept { return _id2offset; }

	private:
		IDDatabase() { load(); }

		IDDatabase(const IDDatabase&) = delete;
		IDDatabase(IDDatabase&&) = delete;

		~IDDatabase() = default;

		IDDatabase& operator=(const IDDatabase&) = delete;
		IDDatabase& operator=(IDDatabase&&) = delete;

		void load()
		{
			const auto version = Module::get().version();
			auto path = "Data/F4SE/Plugins/version-"s;
			path += version.string();
			path += ".bin"sv;

			_mmap.open(path);
			_id2offset = stl::span{
				reinterpret_cast<const mapping_t*>(_mmap.data() + sizeof(std::uint64_t)),
				*reinterpret_cast<const std::uint64_t*>(_mmap.data())
			};
		}

		boost::iostreams::mapped_file_source _mmap;
		stl::span<const mapping_t> _id2offset;
	};

	class Offset
	{
	public:
		constexpr Offset() noexcept = default;

		constexpr Offset(std::size_t a_offset) noexcept :
			_offset(a_offset)
		{}

		constexpr Offset& operator=(std::size_t a_offset) noexcept
		{
			_offset = a_offset;
			return *this;
		}

		[[nodiscard]] std::uintptr_t address() const { return base() + offset(); }
		[[nodiscard]] constexpr std::size_t offset() const noexcept { return _offset; }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::size_t _offset{ 0 };
	};

	class ID
	{
	public:
		constexpr ID() noexcept = default;

		explicit constexpr ID(std::uint64_t a_id) noexcept :
			_id(a_id)
		{}

		constexpr ID& operator=(std::uint64_t a_id) noexcept
		{
			_id = a_id;
			return *this;
		}

		[[nodiscard]] std::uintptr_t address() const { return base() + offset(); }
		[[nodiscard]] constexpr std::uint64_t id() const noexcept { return _id; }
		[[nodiscard]] std::size_t offset() const { return IDDatabase::get().id2offset(_id); }

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::uint64_t _id{ 0 };
	};

	template <class T>
	class Relocation
	{
	public:
		using value_type =
			std::conditional_t<
				std::disjunction_v<
					std::is_member_pointer<T>,
					std::is_function<
						std::remove_pointer_t<T>>>,
				std::decay_t<T>,
				T>;

		constexpr Relocation() noexcept = default;

		explicit constexpr Relocation(std::uintptr_t a_address) noexcept :
			_impl{ a_address }
		{}

		explicit Relocation(Offset a_offset) :
			_impl{ a_offset.address() }
		{}

		explicit Relocation(ID a_id) :
			_impl{ a_id.address() }
		{}

		explicit Relocation(ID a_id, std::ptrdiff_t a_offset) :
			_impl{ a_id.address() + a_offset }
		{}

		constexpr Relocation& operator=(std::uintptr_t a_address) noexcept
		{
			_impl = a_address;
			return *this;
		}

		Relocation& operator=(Offset a_offset)
		{
			_impl = a_offset.address();
			return *this;
		}

		Relocation& operator=(ID a_id)
		{
			_impl = a_id.address();
			return *this;
		}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_pointer_v<U>,
				int> = 0>
		[[nodiscard]] decltype(auto) operator*() const noexcept
		{
			return *get();
		}

		template <
			class U = value_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_pointer<U>,
					std::disjunction<
						std::is_class<std::remove_pointer_t<U>>,
						std::is_enum<std::remove_pointer_t<U>>>>,
				int> = 0>
		[[nodiscard]] auto operator->() const noexcept
		{
			return get();
		}

		template <
			class... Args,
			std::enable_if_t<
				std::is_invocable_v<const value_type&, Args&&...>,
				int> = 0>
		std::invoke_result_t<const value_type&, Args&&...> operator()(Args&&... a_args) const noexcept(
			std::is_nothrow_invocable_v<const value_type&, Args&&...>)
		{
			return REL::invoke(get(), std::forward<Args>(a_args)...);
		}

		[[nodiscard]] constexpr std::uintptr_t address() const noexcept { return _impl; }
		[[nodiscard]] std::size_t offset() const { return _impl - base(); }

		[[nodiscard]] value_type get() const noexcept(std::is_nothrow_copy_constructible_v<value_type>)
		{
			assert(_impl != 0);
			return unrestricted_cast<value_type>(_impl);
		}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_same_v<
					U,
					std::uintptr_t>,
				int> = 0>
		std::uintptr_t write_vfunc(std::size_t a_idx, std::uintptr_t a_newFunc)
		{
			const auto addr = address() + (sizeof(void*) * a_idx);
			const auto result = *reinterpret_cast<std::uintptr_t*>(addr);
			safe_write(addr, a_newFunc);
			return result;
		}

		template <
			class F,
			class U = value_type,
			std::enable_if_t<
				std::is_same_v<
					U,
					std::uintptr_t>,
				int> = 0>
		std::uintptr_t write_vfunc(std::size_t a_idx, F a_newFunc)
		{
			return write_vfunc(a_idx, unrestricted_cast<std::uintptr_t>(a_newFunc));
		}

	private:
		[[nodiscard]] static std::uintptr_t base() { return Module::get().base(); }

		std::uintptr_t _impl{ 0 };
	};
}

#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL

#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL
