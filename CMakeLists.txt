cmake_minimum_required(VERSION 3.19)

set(Boost_USE_STATIC_RUNTIME OFF CACHE BOOL "")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "")
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_SOURCE_DIR}/ports" CACHE STRING "")
set(VCPKG_TARGET_TRIPLET "x64-windows-static-md" CACHE STRING "")

project(umbrella)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(
		FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
	)
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_RUNTIME ON)

if (MSVC)
	add_compile_options(
		/MP	# Build with Multiple Processes
	)
endif()

function(conditionally_add_subdirectory SRC_DIR)
	if(NOT TARGET ${SUBDIRECTORY})
		if (${ARGC} GREATER 1)
			add_subdirectory(${SRC_DIR} ${ARGV1})
		else()
			add_subdirectory(${SRC_DIR})
		endif()
	endif()
endfunction()

conditionally_add_subdirectory(AddressLibDecoder)
conditionally_add_subdirectory(AddressLibGen)
conditionally_add_subdirectory(CommonLibF4)
conditionally_add_subdirectory(ExampleProject)
conditionally_add_subdirectory(F4SEStub/runtime f4se_runtime)
conditionally_add_subdirectory(F4SEStub/loader f4se_loader)
conditionally_add_subdirectory(RTTIDump)
conditionally_add_subdirectory(Tests)
