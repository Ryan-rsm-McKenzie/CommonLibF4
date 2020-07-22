#pragma once

#include "F4SE/F4SE.h"
#include "RE/Fallout.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <utility>
#include <vector>

#include <DbgHelp.h>

#include <boost/algorithm/searching/knuth_morris_pratt.hpp>
#include <boost/regex.hpp>
#include <robin_hood.h>
#include <spdlog/sinks/basic_file_sink.h>

#ifndef NDEBUG
#include <spdlog/sinks/msvc_sink.h>
#endif

#define DLLEXPORT __declspec(dllexport)

namespace logger = F4SE::log;
namespace stl = F4SE::stl;
using namespace std::literals;
