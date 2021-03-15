#pragma once

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
//#define NONLS
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

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <regex>
#include <span>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#pragma warning(push)
#include <args.hxx>
#include <boost/nowide/convert.hpp>
#include <boost/nowide/iostream.hpp>
#include <fmt/format.h>
#include <frozen/map.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <Windows.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <xbyak/xbyak.h>
#pragma warning(pop)

using namespace std::literals;
