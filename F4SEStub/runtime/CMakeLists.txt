include("cmake/sourcelist.cmake")

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
	MISC_FILES
		"${CMAKE_CURRENT_BINARY_DIR}/include/Version.h"
		"${CMAKE_CURRENT_BINARY_DIR}/version.rc"
	PRECOMPILED_HEADERS
		"src/PCH.h"
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
	TREE "${CMAKE_CURRENT_BINARY_DIR}"
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/include/Version.h"
)

if(NOT TARGET CommonLibF4)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../CommonLibF4" CommonLibF4)
endif()

find_package(spdlog REQUIRED CONFIG)

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		CommonLibF4::CommonLibF4
		spdlog::spdlog
)

target_compile_options(
	"${PROJECT_NAME}"
	PRIVATE
		"/Zc:preprocessor"	# Enable preprocessor conformance mode
)

copy_files(
	"$<TARGET_FILE:${PROJECT_NAME}>" "Data/F4SE/Plugins/"
	"$<TARGET_PDB_FILE:${PROJECT_NAME}>" "Data/F4SE/Plugins/"
)
