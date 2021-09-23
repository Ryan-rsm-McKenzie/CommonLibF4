#pragma once

#include "F4SE/F4SE.h"
#include "RE/Fallout.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <fstream>
#include <functional>
#include <memory>
#include <span>
#include <tuple>
#include <utility>
#include <vector>

#include <robin_hood.h>
#include <srell.hpp>

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif

#define DLLEXPORT __declspec(dllexport)

namespace logger = F4SE::log;
namespace stl = F4SE::stl;
using namespace std::literals;

namespace WinAPI
{
	inline constexpr auto UNDNAME_NO_MS_KEYWORDS = static_cast<std::uint32_t>(0x0002);
	inline constexpr auto UNDNAME_NO_FUNCTION_RETURNS = static_cast<std::uint32_t>(0x0004);
	inline constexpr auto UNDNAME_NO_ALLOCATION_MODEL = static_cast<std::uint32_t>(0x0008);
	inline constexpr auto UNDNAME_NO_ALLOCATION_LANGUAGE = static_cast<std::uint32_t>(0x0010);
	inline constexpr auto UNDNAME_NO_THISTYPE = static_cast<std::uint32_t>(0x0060);
	inline constexpr auto UNDNAME_NO_ACCESS_SPECIFIERS = static_cast<std::uint32_t>(0x0080);
	inline constexpr auto UNDNAME_NO_THROW_SIGNATURES = static_cast<std::uint32_t>(0x0100);
	inline constexpr auto UNDNAME_NO_RETURN_UDT_MODEL = static_cast<std::uint32_t>(0x0400);
	inline constexpr auto UNDNAME_NAME_ONLY = static_cast<std::uint32_t>(0x1000);
	inline constexpr auto UNDNAME_NO_ARGUMENTS = static_cast<std::uint32_t>(0x2000);

	[[nodiscard]] std::uint32_t(UnDecorateSymbolName)(
		const char* a_name,
		char* a_outputString,
		std::uint32_t a_maxStringLength,
		std::uint32_t a_flags) noexcept;
}
