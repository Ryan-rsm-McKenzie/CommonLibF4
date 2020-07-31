#pragma once

#pragma warning(error : 4715)  // 'function' : not all control paths return a value

#pragma warning(disable : 4200)	 // nonstandard extension used : zero-sized array in struct/union
#pragma warning(disable : 4324)	 // 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable : 4371)	 // 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
#pragma warning(disable : 4686)	 // 'user-defined type' : possible change in behavior, change in UDT return calling convention
#pragma warning(disable : 5220)	 // 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial

#define WINVER 0x0601  // Windows 7
#define _WIN32_WINNT 0x0601

#define WIN32_LEAN_AND_MEAN

#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
//#define NOWINMESSAGES
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
//#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NOKERNEL
//#define NOUSER
#define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
//#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX

#define SPDLOG_COMPILED_LIB
#define XBYAK_NO_OP_NAMES

#include <Windows.h>

#include <ShlObj.h>

#undef GetFileAttributes

#include <array>
#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <functional>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <nonstd/span.hpp>
#include <spdlog/spdlog.h>

#include "F4SE/Impl/Atomic.h"

namespace F4SE
{
	using namespace std::literals;

	inline namespace util
	{
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr auto to_underlying(Enum a_val) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<underlying_type_t>(a_val);
		}

		template <class To, class From>
		[[nodiscard]] inline To unrestricted_cast(From a_from) noexcept(std::is_nothrow_move_assignable_v<From>)
		{
			if constexpr (std::is_same_v<
							  std::remove_cv_t<From>,
							  std::remove_cv_t<To>>) {
				return To{ a_from };

				// From != To
			} else if constexpr (std::is_reference_v<From>) {
				return unrestricted_cast<To>(std::addressof(a_from));

				// From: NOT reference
			} else if constexpr (std::is_reference_v<To>) {
				return *unrestricted_cast<
					std::add_pointer_t<
						std::remove_reference_t<To>>>(a_from);

				// To: NOT reference
			} else if constexpr (std::is_pointer_v<From> &&
								 std::is_pointer_v<To>) {
				return static_cast<To>(
					const_cast<void*>(
						static_cast<const volatile void*>(a_from)));
			} else if constexpr ((std::is_pointer_v<From> && std::is_integral_v<To>) ||
								 (std::is_integral_v<From> && std::is_pointer_v<To>)) {
				return reinterpret_cast<To>(a_from);
			} else {
				union
				{
					std::remove_cv_t<std::remove_reference_t<From>> from;
					std::remove_cv_t<std::remove_reference_t<To>> to;
				};

				from = std::forward<From>(a_from);
				return to;
			}
		}

		template <class T, class U>
		[[nodiscard]] inline auto adjust_pointer(U* a_ptr, std::ptrdiff_t a_adjust) noexcept
		{
			auto addr = a_ptr ? reinterpret_cast<std::uintptr_t>(a_ptr) + a_adjust : 0;
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
	}

	namespace stl
	{
		using nonstd::span;

		using zstring = std::string_view;
		using zwstring = std::wstring_view;

		struct source_location
		{
		public:
			constexpr source_location() noexcept = default;
			constexpr source_location(const source_location&) noexcept = default;
			constexpr source_location(source_location&&) noexcept = default;

			~source_location() noexcept = default;

			constexpr source_location& operator=(const source_location&) noexcept = default;
			constexpr source_location& operator=(source_location&&) noexcept = default;

			[[nodiscard]] static constexpr source_location current(
				std::uint_least32_t a_line = __builtin_LINE(),
				std::uint_least32_t a_column = __builtin_COLUMN(),
				const char* a_fileName = __builtin_FILE(),
				const char* a_functionName = __builtin_FUNCTION()) noexcept { return { a_line, a_column, a_fileName, a_functionName }; }

			[[nodiscard]] constexpr std::uint_least32_t line() const noexcept { return _line; }
			[[nodiscard]] constexpr std::uint_least32_t column() const noexcept { return _column; }
			[[nodiscard]] constexpr const char* file_name() const noexcept { return _fileName; }
			[[nodiscard]] constexpr const char* function_name() const noexcept { return _functionName; }

		protected:
			constexpr source_location(
				std::uint_least32_t a_line,
				std::uint_least32_t a_column,
				const char* a_fileName,
				const char* a_functionName) noexcept :
				_line(a_line),
				_column(a_column),
				_fileName(a_fileName),
				_functionName(a_functionName)
			{}

		private:
			std::uint_least32_t _line{ 0 };
			std::uint_least32_t _column{ 0 };
			const char* _fileName{ "" };
			const char* _functionName{ "" };
		};

		template <class, class, class = void>
		class enumeration;

		template <
			class Enum,
			class Underlying>
		class enumeration<
			Enum,
			Underlying,
			std::enable_if_t<
				std::conjunction_v<
					std::is_enum<Enum>,
					std::is_integral<Underlying>>>>
		{
		public:
			using enum_type = Enum;
			using underlying_type = Underlying;

			constexpr enumeration() noexcept = default;

			constexpr enumeration(const enumeration&) noexcept = default;

			constexpr enumeration(enumeration&&) noexcept = default;

			template <class U2>
			constexpr enumeration(enumeration<Enum, U2> a_rhs) noexcept :
				_impl(static_cast<underlying_type>(a_rhs.get()))
			{}

			template <
				class... Args,
				std::enable_if_t<
					std::conjunction_v<
						std::is_same<
							Args,
							enum_type>...>,
					int> = 0>
			constexpr enumeration(Args... a_values) noexcept :
				_impl((static_cast<underlying_type>(a_values) | ...))
			{}

			~enumeration() noexcept = default;

			constexpr enumeration& operator=(const enumeration&) noexcept = default;
			constexpr enumeration& operator=(enumeration&&) noexcept = default;

			template <class U2>
			constexpr enumeration& operator=(enumeration<Enum, U2> a_rhs) noexcept
			{
				_impl = static_cast<underlying_type>(a_rhs.get());
			}

			constexpr enumeration& operator=(enum_type a_value) noexcept
			{
				_impl = static_cast<underlying_type>(a_value);
				return *this;
			}

			[[nodiscard]] explicit constexpr operator bool() const noexcept { return _impl != static_cast<underlying_type>(0); }

			[[nodiscard]] constexpr enum_type operator*() const noexcept { return get(); }
			[[nodiscard]] constexpr enum_type get() const noexcept { return static_cast<enum_type>(_impl); }
			[[nodiscard]] constexpr underlying_type underlying() const noexcept { return _impl; }

			template <
				class... Args,
				std::enable_if_t<
					std::conjunction_v<
						std::is_same<
							Args,
							enum_type>...>,
					int> = 0>
			constexpr enumeration& set(Args... a_args) noexcept
			{
				_impl |= (static_cast<underlying_type>(a_args) | ...);
				return *this;
			}

			template <
				class... Args,
				std::enable_if_t<
					std::conjunction_v<
						std::is_same<
							Args,
							enum_type>...>,
					int> = 0>
			constexpr enumeration& reset(Args... a_args) noexcept
			{
				_impl &= ~(static_cast<underlying_type>(a_args) | ...);
				return *this;
			}

			template <
				class... Args,
				std::enable_if_t<
					std::conjunction_v<
						std::is_same<
							Args,
							enum_type>...>,
					int> = 0>
			[[nodiscard]] constexpr bool any(Args... a_args) const noexcept
			{
				return (_impl & (static_cast<underlying_type>(a_args) | ...)) != static_cast<underlying_type>(0);
			}

			template <
				class... Args,
				std::enable_if_t<
					std::conjunction_v<
						std::is_same<
							Args,
							enum_type>...>,
					int> = 0>
			[[nodiscard]] constexpr bool all(Args... a_args) const noexcept
			{
				return (_impl & (static_cast<underlying_type>(a_args) | ...)) == (static_cast<underlying_type>(a_args) | ...);
			}

			template <
				class... Args,
				std::enable_if_t<
					std::conjunction_v<
						std::is_same<
							Args,
							enum_type>...>,
					int> = 0>
			[[nodiscard]] constexpr bool none(Args... a_args) const noexcept
			{
				return (_impl & (static_cast<underlying_type>(a_args) | ...)) == static_cast<underlying_type>(0);
			}

		private:
			underlying_type _impl{ 0 };
		};

		template <class E>
		enumeration(E) -> enumeration<E, std::underlying_type_t<E>>;
	}
}

#define F4SE_MAKE_LOGICAL_OP(a_op)                                                                          \
	template <                                                                                              \
		class E,                                                                                            \
		class U1,                                                                                           \
		class U2>                                                                                           \
	[[nodiscard]] constexpr bool operator a_op(enumeration<E, U1> a_lhs, enumeration<E, U2> a_rhs) noexcept \
	{                                                                                                       \
		return a_lhs.get() a_op a_rhs.get();                                                                \
	}                                                                                                       \
                                                                                                            \
	template <                                                                                              \
		class E,                                                                                            \
		class U>                                                                                            \
	[[nodiscard]] constexpr bool operator a_op(enumeration<E, U> a_lhs, E a_rhs) noexcept                   \
	{                                                                                                       \
		return a_lhs.get() a_op a_rhs;                                                                      \
	}                                                                                                       \
                                                                                                            \
	template <                                                                                              \
		class E,                                                                                            \
		class U>                                                                                            \
	[[nodiscard]] constexpr bool operator a_op(E a_lhs, enumeration<E, U> a_rhs) noexcept                   \
	{                                                                                                       \
		return a_lhs a_op a_rhs.get();                                                                      \
	}

#define F4SE_MAKE_ARITHMETIC_OP(a_op)                                                        \
	template <                                                                               \
		class E,                                                                             \
		class U>                                                                             \
	[[nodiscard]] constexpr auto operator a_op(enumeration<E, U> a_enum, U a_shift) noexcept \
		->enumeration<E, U>                                                                  \
	{                                                                                        \
		return static_cast<E>(static_cast<U>(a_enum.get()) a_op a_shift);                    \
	}                                                                                        \
                                                                                             \
	template <                                                                               \
		class E,                                                                             \
		class U>                                                                             \
	constexpr auto operator a_op##=(enumeration<E, U>& a_enum, U a_shift) noexcept           \
		->enumeration<E, U>&                                                                 \
	{                                                                                        \
		return a_enum = a_enum a_op a_shift;                                                 \
	}

#define F4SE_MAKE_ENUMERATION_OP(a_op)                                                                      \
	template <                                                                                              \
		class E,                                                                                            \
		class U1,                                                                                           \
		class U2>                                                                                           \
	[[nodiscard]] constexpr auto operator a_op(enumeration<E, U1> a_lhs, enumeration<E, U2> a_rhs) noexcept \
		->enumeration<E, std::common_type_t<U1, U2>>                                                        \
	{                                                                                                       \
		return static_cast<E>(static_cast<U1>(a_lhs.get()) a_op static_cast<U2>(a_rhs.get()));              \
	}                                                                                                       \
                                                                                                            \
	template <                                                                                              \
		class E,                                                                                            \
		class U>                                                                                            \
	[[nodiscard]] constexpr auto operator a_op(enumeration<E, U> a_lhs, E a_rhs) noexcept                   \
		->enumeration<E, U>                                                                                 \
	{                                                                                                       \
		return static_cast<E>(static_cast<U>(a_lhs.get()) a_op static_cast<U>(a_rhs));                      \
	}                                                                                                       \
                                                                                                            \
	template <                                                                                              \
		class E,                                                                                            \
		class U>                                                                                            \
	[[nodiscard]] constexpr auto operator a_op(E a_lhs, enumeration<E, U> a_rhs) noexcept                   \
		->enumeration<E, U>                                                                                 \
	{                                                                                                       \
		return static_cast<E>(static_cast<U>(a_lhs) a_op static_cast<U>(a_rhs.get()));                      \
	}                                                                                                       \
                                                                                                            \
	template <                                                                                              \
		class E,                                                                                            \
		class U1,                                                                                           \
		class U2>                                                                                           \
	constexpr auto operator a_op##=(enumeration<E, U1>& a_lhs, enumeration<E, U2> a_rhs) noexcept           \
		->enumeration<E, U1>&                                                                               \
	{                                                                                                       \
		return a_lhs = a_lhs a_op a_rhs;                                                                    \
	}                                                                                                       \
                                                                                                            \
	template <                                                                                              \
		class E,                                                                                            \
		class U>                                                                                            \
	constexpr auto operator a_op##=(enumeration<E, U>& a_lhs, E a_rhs) noexcept                             \
		->enumeration<E, U>&                                                                                \
	{                                                                                                       \
		return a_lhs = a_lhs a_op a_rhs;                                                                    \
	}                                                                                                       \
                                                                                                            \
	template <                                                                                              \
		class E,                                                                                            \
		class U>                                                                                            \
	constexpr auto operator a_op##=(E& a_lhs, enumeration<E, U> a_rhs) noexcept                             \
		->E&                                                                                                \
	{                                                                                                       \
		return a_lhs = *(a_lhs a_op a_rhs);                                                                 \
	}

#define F4SE_MAKE_INCREMENTER_OP(a_op)                                                       \
	template <                                                                               \
		class E,                                                                             \
		class U>                                                                             \
	constexpr auto operator a_op##a_op(enumeration<E, U>& a_lhs) noexcept                    \
		->enumeration<E, U>&                                                                 \
	{                                                                                        \
		return a_lhs a_op## = static_cast<E>(1);                                             \
	}                                                                                        \
                                                                                             \
	template <                                                                               \
		class E,                                                                             \
		class U>                                                                             \
	[[nodiscard]] constexpr auto operator a_op##a_op(enumeration<E, U>& a_lhs, int) noexcept \
		->enumeration<E, U>                                                                  \
	{                                                                                        \
		auto tmp = a_lhs;                                                                    \
		a_op##a_op a_lhs;                                                                    \
		return tmp;                                                                          \
	}

namespace F4SE
{
	namespace stl
	{
		template <
			class E,
			class U>
		[[nodiscard]] constexpr auto operator~(enumeration<E, U> a_enum) noexcept
			-> enumeration<E, U>
		{
			return static_cast<E>(~static_cast<U>(a_enum.get()));
		}

		F4SE_MAKE_LOGICAL_OP(==);
		F4SE_MAKE_LOGICAL_OP(!=);
		F4SE_MAKE_LOGICAL_OP(<);
		F4SE_MAKE_LOGICAL_OP(<=);
		F4SE_MAKE_LOGICAL_OP(>);
		F4SE_MAKE_LOGICAL_OP(>=);

		F4SE_MAKE_ARITHMETIC_OP(<<);
		F4SE_MAKE_ENUMERATION_OP(<<);
		F4SE_MAKE_ARITHMETIC_OP(>>);
		F4SE_MAKE_ENUMERATION_OP(>>);

		F4SE_MAKE_ENUMERATION_OP(|);
		F4SE_MAKE_ENUMERATION_OP(&);
		F4SE_MAKE_ENUMERATION_OP(^);

		F4SE_MAKE_ENUMERATION_OP(+);
		F4SE_MAKE_ENUMERATION_OP(-);

		F4SE_MAKE_INCREMENTER_OP(+);  // ++
		F4SE_MAKE_INCREMENTER_OP(-);  // --
	}
}

#undef F4SE_MAKE_INCREMENTER_OP
#undef F4SE_MAKE_ENUMERATION_OP
#undef F4SE_MAKE_ARITHMETIC_OP
#undef F4SE_MAKE_LOGICAL_OP

namespace RE
{
	using namespace std::literals;
	using namespace F4SE::util;
	namespace stl = F4SE::stl;
}

namespace REL
{
	using namespace std::literals;
	using namespace F4SE::util;
	namespace stl = F4SE::stl;
}

#include "REL/Relocation.h"

#include "RE/NiRTTI_IDs.h"
#include "RE/RTTI_IDs.h"
