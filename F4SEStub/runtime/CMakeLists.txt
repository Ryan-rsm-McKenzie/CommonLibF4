cmake_minimum_required(VERSION 3.20)

include("cmake/sourcelist.cmake")

include(../../cmake/common.cmake)
add_project(
	TARGET_TYPE LIBRARY
	LIBRARY_TYPE SHARED
	PROJECT f4se_runtime
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		"${CMAKE_CURRENT_BINARY_DIR}/include"
		src
	GROUPED_FILES
		${SOURCES}
		.clang-format
	MISC_FILES
		"${CMAKE_CURRENT_BINARY_DIR}/include/Version.h"
		"${CMAKE_CURRENT_BINARY_DIR}/version.rc"
	PRECOMPILED_HEADERS
		src/PCH.h
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.h.in"
	"${CMAKE_CURRENT_BINARY_DIR}/include/Version.h"
	@ONLY
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in"
	"${CMAKE_CURRENT_BINARY_DIR}/version.rc"
	@ONLY
)

source_group(
	TREE ${CMAKE_CURRENT_BINARY_DIR}
	FILES "${CMAKE_CURRENT_BINARY_DIR}/include/Version.h"
)

set(Boost_USE_STATIC_LIBS ON)

if (NOT TARGET CommonLibF4)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../CommonLibF4" CommonLibF4)
endif ()

find_package(spdlog REQUIRED CONFIG)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		CommonLibF4::CommonLibF4
		spdlog::spdlog
)

copy_files(
	"$<TARGET_FILE:${PROJECT_NAME}>" "Data/F4SE/Plugins/"
	"$<TARGET_PDB_FILE:${PROJECT_NAME}>" "Data/F4SE/Plugins/"
)
