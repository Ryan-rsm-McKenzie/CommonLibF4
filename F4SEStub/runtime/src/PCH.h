#pragma once

#pragma warning(push)
#include "F4SE/F4SE.h"
#include "RE/Fallout.h"

namespace WinAPI = F4SE::WinAPI;

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif
#pragma warning(pop)

#define DLLEXPORT __declspec(dllexport)

namespace logger
{
	using namespace F4SE::log;
}

namespace stl = F4SE::stl;

using namespace std::literals;

#include "Version.h"
