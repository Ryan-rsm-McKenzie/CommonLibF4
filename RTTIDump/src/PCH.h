#pragma once

#include "F4SE/F4SE.h"
#include "RE/Fallout.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <utility>
#include <vector>

#include <boost/algorithm/searching/knuth_morris_pratt.hpp>
#include <boost/regex.hpp>
#include <robin_hood.h>

#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif

#define DLLEXPORT __declspec(dllexport)

namespace logger = F4SE::log;
namespace stl = F4SE::stl;
using namespace std::literals;

namespace WinAPI
{
	inline constexpr auto(UNDNAME_NO_ARGUMENTS){ static_cast<std::uint32_t>(0x2000) };

	[[nodiscard]] std::uint32_t(UnDecorateSymbolName)(
		const char* a_name,
		char* a_outputString,
		std::uint32_t a_maxStringLength,
		std::uint32_t a_flags) noexcept;
}
