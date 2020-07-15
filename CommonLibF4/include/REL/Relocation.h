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
				std::bool_constant<sizeof(T) == 8>,
				std::bool_constant<sizeof(T) == 16>,
				std::bool_constant<sizeof(T) == 32>,
				std::bool_constant<sizeof(T) == 64>>
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
		class... Args>
	std::invoke_result_t<F, Args...> invoke(F&& a_func, Args&&... a_args) noexcept(
		std::is_nothrow_invocable<F, Args...>)
	{
		if constexpr (std::is_function_v<F>) {
			return a_func(std::forward<Args>(a_args)...);
		} else if constexpr (std::is_member_function_pointer_v<F>) {
			if constexpr (detail::is_x64_pod_v<std::invoke_result_t<F, Args...>>) {	 // member functions == free functions in x64
				using func_t = detail::member_function_pod_type_t<F>;
				auto func = unrestricted_cast<func_t*>(std::forward<F>(a_func));
				return func(std::forward<Args>(a_args));
			} else {  // shift args to insert result
				return detail::invoke_member_function_non_pod(std::forward<F>(a_func), std::forward<Args>(a_args)...);
			}
		} else {
			static_assert(false);
		}
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

		[[nodiscard]] constexpr reference		operator[](std::size_t a_idx) noexcept { return _impl[a_idx]; }
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

		[[nodiscard]] inline std::string string() const
		{
			std::string result;
			for (std::size_t i = 0; i < _impl.size(); ++i) {
				result += std::to_string(_impl[i]);
				result += '-';
			}
			result.pop_back();
			return result;
		}

		[[nodiscard]] inline std::wstring wstring() const
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

	class Module
	{
	public:
		[[nodiscard]] static inline Module& get() noexcept
		{
			static Module singleton;
			return singleton;
		}

		[[nodiscard]] constexpr std::uintptr_t address() const noexcept { return _address; }

		inline void load()
		{
			constexpr auto filename = L"Fallout4.exe"sv;

			auto handle = GetModuleHandleW(filename.data());
			if (handle == nullptr) {
				throw std::runtime_error("Failed to obtain module handle"s);
			}
			_address = reinterpret_cast<std::uintptr_t>(handle);

			DWORD			  dummy;
			std::vector<char> buf(GetFileVersionInfoSizeW(filename.data(), std::addressof(dummy)));
			if (buf.size() == 0) {
				throw std::runtime_error("Failed to obtain file version info size"s);
			}

			if (!GetFileVersionInfoW(filename.data(), 0, static_cast<DWORD>(buf.size()), buf.data())) {
				throw std::runtime_error("Failed to obtain file version info"s);
			}

			LPVOID verBuf;
			UINT   verLen;
			if (!VerQueryValueW(buf.data(), L"\\StringFileInfo\\040904B0\\ProductVersion", std::addressof(verBuf), std::addressof(verLen))) {
				throw std::runtime_error("Failed to query value"s);
			}

			std::istringstream ss(
				std::string(static_cast<const char*>(verBuf), verLen));
			std::string token;
			for (std::size_t i = 0; i < 4 && std::getline(ss, token, '.'); ++i) {
				_version[i] = static_cast<std::uint16_t>(std::stoi(token));
			}
		}

		[[nodiscard]] constexpr Version version() const noexcept { return _version; }

	private:
		constexpr Module() noexcept = default;
		Module(const Module&) = delete;
		Module(Module&&) = delete;

		~Module() noexcept = default;

		Module& operator=(const Module&) = delete;
		Module& operator=(Module&&) = delete;

		Version		   _version;
		std::uintptr_t _address{ 0 };
	};

	class IDDatabase
	{
	public:
		static inline IDDatabase& get()
		{
			static IDDatabase singleton;
			return singleton;
		}

		inline void load()
		{
			const auto	 version = Module::get().version();
			std::wstring path(L"F4SE/Plugins/version-"sv);
			path += version.wstring();
			path += L".bin"sv;

			_mmap.map(path);
			_id2offset = stl::span(
				reinterpret_cast<const mapping*>(_mmap.data() + sizeof(std::uint64_t)),
				*reinterpret_cast<const std::uint64_t*>(_mmap.data()));

#ifndef NDEBUG
			_offset2id.clear();
			_offset2id.reserve(_id2offset.size());
			_offset2id.insert(_offset2id.begin(), _id2offset.begin(), _id2offset.end());
			std::sort(
				_offset2id.begin(),
				_offset2id.end(),
				[](auto&& a_lhs, auto&& a_rhs) {
					return a_lhs.offset < a_rhs.offset;
				});
#endif
		}

		[[nodiscard]] inline std::size_t id2offset(std::uint64_t a_id)
		{
			if (_id2offset.empty()) {
				throw std::runtime_error("data is empty"s);
			}

			mapping elem{ a_id, 0 };
			auto	it = std::lower_bound(
				   _id2offset.begin(),
				   _id2offset.end(),
				   elem,
				   [](auto&& a_lhs, auto&& a_rhs) {
					   return a_lhs.id < a_rhs.id;
				   });
			if (it == _id2offset.end()) {
				throw std::runtime_error("id not found"s);
			}

			return static_cast<std::size_t>(it->offset);
		}

#ifndef NDEBUG
		[[nodiscard]] inline std::uint64_t offset2id(std::size_t a_offset)
		{
			if (_offset2id.empty()) {
				throw std::runtime_error("data is empty"s);
			}

			mapping elem{ 0, a_offset };
			auto	it = std::lower_bound(
				   _offset2id.begin(),
				   _offset2id.end(),
				   elem,
				   [](auto&& a_lhs, auto&& a_rhs) {
					   return a_lhs.offset < a_rhs.offset;
				   });
			if (it == _offset2id.end()) {
				throw std::runtime_error("offset not found"s);
			}

			return it->id;
		}
#endif

	private:
		class memory_map
		{
		public:
			constexpr memory_map() noexcept = default;

			memory_map(const memory_map&) = delete;

			constexpr memory_map(memory_map&& a_rhs) noexcept :
				_file(a_rhs._file),
				_mapping(a_rhs._mapping),
				_view(a_rhs._view)
			{
				a_rhs._file = INVALID_HANDLE_VALUE;
				a_rhs._mapping = nullptr;
				a_rhs._view = nullptr;
			}

			inline ~memory_map() { unmap(); }

			memory_map& operator=(const memory_map&) = delete;

			constexpr memory_map& operator=(memory_map&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_file = a_rhs._file;
					_mapping = a_rhs._mapping;
					_view = a_rhs._view;

					a_rhs._file = INVALID_HANDLE_VALUE;
					a_rhs._mapping = nullptr;
					a_rhs._view = nullptr;
				}
				return *this;
			}

			inline void map(std::wstring_view a_fileName)
			{
				_file = CreateFileW(
					a_fileName.data(),
					FILE_GENERIC_READ,
					FILE_SHARE_READ,
					nullptr,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					nullptr);
				if (_file == INVALID_HANDLE_VALUE) {
					throw std::runtime_error("failed to create file"s);
				}

				_mapping = CreateFileMappingW(
					_file,
					nullptr,
					PAGE_READONLY,
					0,
					0,
					a_fileName.data());
				if (_mapping == nullptr) {
					throw std::runtime_error("failed to create file mapping"s);
				}

				_view = MapViewOfFile(
					_mapping,
					FILE_MAP_READ,
					0,
					0,
					0);
				if (_view == nullptr) {
					throw std::runtime_error("failed to map view of file"s);
				}
			}

			inline void unmap()
			{
				if (_view != nullptr) {
					if (UnmapViewOfFile(_view) == 0) {
						assert(false);
					}
					_view = nullptr;
				}

				if (_mapping != nullptr) {
					if (CloseHandle(_mapping) == 0) {
						assert(false);
					}
					_mapping = nullptr;
				}

				if (_file != INVALID_HANDLE_VALUE) {
					if (CloseHandle(_file) == 0) {
						assert(false);
					}
					_file = INVALID_HANDLE_VALUE;
				}
			}

			[[nodiscard]] constexpr const std::byte* data() const noexcept { return static_cast<const std::byte*>(_view); }

		private:
			HANDLE		_file{ INVALID_HANDLE_VALUE };
			HANDLE		_mapping{ nullptr };
			const void* _view{ nullptr };
		};

		struct mapping
		{
			std::uint64_t id;
			std::uint64_t offset;
		};

		IDDatabase() noexcept = default;
		IDDatabase(const IDDatabase&) = delete;
		IDDatabase(IDDatabase&&) = delete;

		~IDDatabase() = default;

		IDDatabase& operator=(const IDDatabase&) = delete;
		IDDatabase& operator=(IDDatabase&&) = delete;

		memory_map				 _mmap;
		stl::span<const mapping> _id2offset;
#ifndef NDEBUG
		std::vector<mapping> _offset2id;
#endif
	};

	class Offset
	{
	public:
		constexpr Offset() noexcept = default;

		explicit inline Offset(std::size_t a_offset) noexcept :
			_address(base() + a_offset)
		{}

		inline Offset& operator=(std::size_t a_offset) noexcept
		{
			_address = base() + a_offset;
			return *this;
		}

		[[nodiscard]] constexpr std::uintptr_t address() const noexcept { return _address; }
		[[nodiscard]] inline std::size_t	   offset() const noexcept { return address() - base(); }

	private:
		[[nodiscard]] static inline std::uintptr_t base() noexcept { return Module::get().address(); }

		std::uintptr_t _address{ 0 };
	};

	class ID
	{
	public:
		constexpr ID() noexcept = default;

		explicit inline ID(std::uint64_t a_id) :
			_address(base() + convert(a_id))
		{}

		inline ID& operator=(std::uint64_t a_id)
		{
			_address = base() + convert(a_id);
			return *this;
		}

		[[nodiscard]] constexpr std::uintptr_t address() const noexcept { return _address; }
		[[nodiscard]] inline std::size_t	   offset() const noexcept { return address() - base(); }

	private:
		[[nodiscard]] static inline std::uintptr_t base() noexcept { return Module::get().address(); }
		[[nodiscard]] static inline std::size_t	   convert(std::uint64_t a_id) { return IDDatabase::get().id2offset(a_id); }

		std::uintptr_t _address{ 0 };
	};

	template <class T>
	class Relocation
	{
	public:
		using value_type = T;

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_default_constructible_v<U>,
				int> = 0>
		Relocation() noexcept(std::is_nothrow_default_constructible_v<U>) :
			_impl{}
		{}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_copy_constructible_v<U>,
				int> = 0>
		explicit Relocation(std::uintptr_t a_address) noexcept(std::is_nothrow_copy_constructible_v<U>) :
			_impl{ unrestricted_cast<value_type>(a_address) }
		{}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_copy_constructible_v<U>,
				int> = 0>
		explicit Relocation(Offset a_offset) noexcept(std::is_nothrow_copy_constructible_v<U>) :
			_impl{ unrestricted_cast<value_type>(a_offset.address()) }
		{}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_copy_constructible_v<U>,
				int> = 0>
		explicit Relocation(ID a_id) noexcept(std::is_nothrow_copy_constructible_v<U>) :
			_impl{ unrestricted_cast<value_type>(a_id.address()) }
		{}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_copy_assignable_v<U>,
				int> = 0>
		Relocation& operator=(std::uintptr_t a_address) noexcept(std::is_nothrow_copy_assignable_v<U>)
		{
			_impl = unrestricted_cast<value_type>(a_address);
			return *this;
		}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_copy_assignable_v<U>,
				int> = 0>
		Relocation& operator=(Offset a_offset) noexcept(std::is_nothrow_copy_assignable_v<U>)
		{
			_impl = unrestricted_cast<value_type>(a_offset.address());
			return *this;
		}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_copy_assignable_v<U>,
				int> = 0>
		Relocation& operator=(ID a_id) noexcept(std::is_nothrow_copy_assignable_v<U>)
		{
			_impl = unrestricted_cast<value_type>(a_id.address());
			return *this;
		}

		template <
			class U = value_type,
			std::enable_if_t<
				std::is_pointer_v<U>,
				int> = 0>
		[[nodiscard]] decltype(auto) operator*() const noexcept
		{
			return *_impl;
		}

		template <
			class U = value_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_pointer_v<U>,
					std::disjunction<
						std::is_class_v<U>,
						std::is_enum_v<U>>>,
				int> = 0>
		[[nodiscard]] auto operator->() const noexcept
		{
			return _impl;
		}

		template <
			class... Args,
			std::enable_if_t<
				std::is_invocable_v<const value_type&, Args&&...>,
				int> = 0>
		std::invoke_result_t<const value_type&, Args&&...> operator()(Args&&... a_args) const noexcept(
			std::is_nothrow_invocable_v<const value_type&, Args&&...>)
		{
			return REL::invoke(_impl, std::forward<Args>(a_args)...);
		}

		[[nodiscard]] std::uintptr_t address() const { return unrestricted_cast<std::uintptr_t>(_impl); }
		[[nodiscard]] std::size_t	 offset() const { offset() - base(); }

	private:
		[[nodiscard]] static std::uintptr_t base() noexcept { return Module::get().address(); }

		value_type _impl;
	};
}

#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_NON_POD_TYPE_HELPER_IMPL

#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER
#undef REL_MAKE_MEMBER_FUNCTION_POD_TYPE_HELPER_IMPL
