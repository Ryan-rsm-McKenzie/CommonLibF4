cmake_minimum_required(VERSION 3.21)
include("cmake/common.cmake")

project(umbrella)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

function(conditionally_add_subdirectory SRC_DIR)
	if(NOT TARGET "${SUBDIRECTORY}")
		if("${ARGC}" GREATER 1)
			add_subdirectory("${SRC_DIR}" "${ARGV1}")
		else()
			add_subdirectory("${SRC_DIR}")
		endif()
	endif()
endfunction()

include(CTest)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

conditionally_add_subdirectory(AddressLibDecoder)
conditionally_add_subdirectory(AddressLibGen)
conditionally_add_subdirectory(CommonLibF4)
conditionally_add_subdirectory(ExampleProject)
conditionally_add_subdirectory("F4SEStub/runtime" f4se_runtime)
conditionally_add_subdirectory("F4SEStub/loader" f4se_loader)
conditionally_add_subdirectory("F4SEStub/steam_loader" f4se_steam_loader)
conditionally_add_subdirectory(RTTIDump)
conditionally_add_subdirectory(Tests)
