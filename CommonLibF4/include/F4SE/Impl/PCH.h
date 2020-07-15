#pragma once

#define WINVER		 0x0601	 // Windows 7
#define _WIN32_WINNT 0x0601

#define WIN32_LEAN_AND_MEAN

#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOWINMESSAGES
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
#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NOKERNEL
#define NOUSER
#define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
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

#include <Windows.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <nonstd/span.hpp>

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

		// + operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator+(Enum a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(
				static_cast<underlying_type_t>(a_lhs) +
				static_cast<underlying_type_t>(a_rhs));
		}

		// += operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator+=(Enum& a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_lhs = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_lhs) +
					   static_cast<underlying_type_t>(a_rhs));
		}

		// - operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator-(Enum a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(
				static_cast<underlying_type_t>(a_lhs) -
				static_cast<underlying_type_t>(a_rhs));
		}

		// -= operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator-=(Enum& a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_lhs = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_lhs) -
					   static_cast<underlying_type_t>(a_rhs));
		}

		// ~ operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator~(Enum a_val) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(~static_cast<underlying_type_t>(a_val));
		}

		// & operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator&(Enum a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(
				static_cast<underlying_type_t>(a_lhs) &
				static_cast<underlying_type_t>(a_rhs));
		}

		// &= operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator&=(Enum& a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_lhs = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_lhs) &
					   static_cast<underlying_type_t>(a_rhs));
		}

		// | operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator|(Enum a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(
				static_cast<underlying_type_t>(a_lhs) |
				static_cast<underlying_type_t>(a_rhs));
		}

		// |= operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator|=(Enum& a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_lhs = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_lhs) |
					   static_cast<underlying_type_t>(a_rhs));
		}

		// ^ operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator^(Enum a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(
				static_cast<underlying_type_t>(a_lhs) ^
				static_cast<underlying_type_t>(a_rhs));
		}

		// ^= operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator^=(Enum& a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_lhs = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_lhs) ^
					   static_cast<underlying_type_t>(a_rhs));
		}

		// << operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator<<(Enum a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(
				static_cast<underlying_type_t>(a_lhs)
				<< static_cast<underlying_type_t>(a_rhs));
		}

		// <<= operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator<<=(Enum& a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_lhs = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_lhs)
					   << static_cast<underlying_type_t>(a_rhs));
		}

		// >> operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator>>(Enum a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return static_cast<Enum>(
				static_cast<underlying_type_t>(a_lhs) >>
				static_cast<underlying_type_t>(a_rhs));
		}

		// >>= operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator>>=(Enum& a_lhs, Enum a_rhs) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_lhs = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_lhs) >>
					   static_cast<underlying_type_t>(a_rhs));
		}

		// prefix ++ operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		constexpr Enum& operator++(Enum& a_this) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			return a_this = static_cast<Enum>(
					   static_cast<underlying_type_t>(a_this) +
					   static_cast<underlying_type_t>(1));
		}

		// postfix ++ operator
		template <
			class Enum,
			std::enable_if_t<
				std::is_enum_v<
					Enum>,
				int> = 0>
		[[nodiscard]] constexpr Enum operator++(Enum& a_this, int) noexcept
		{
			using underlying_type_t = std::underlying_type_t<Enum>;
			auto tmp = a_this;
			a_this = static_cast<Enum>(
				static_cast<underlying_type_t>(a_this) +
				static_cast<underlying_type_t>(1));
			return tmp;
		}

		template <class To, class From>
		[[nodiscard]] inline To unrestricted_cast(From a_from)
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
					std::remove_cv_t<std::remove_reference_t<To>>	to;
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
	}
}

namespace RE
{
	using namespace std::literals;
	using namespace ::F4SE::util;
	namespace stl = ::F4SE::stl;
}

namespace REL
{
	using namespace std::literals;
	using namespace ::F4SE::util;
	namespace stl = ::F4SE::stl;
}
