add_project(
	TARGET_TYPE LIBRARY
	LIBRARY_TYPE SHARED
	PROJECT RTTIDump
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		"src/main.cpp"
		"src/PCH.cpp"
		"src/PCH.h"
	PRECOMPILED_HEADERS
		"src/PCH.h"
)

if(NOT TARGET CommonLibF4)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../CommonLibF4" CommonLibF4)
endif()

find_package(robin_hood REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)
find_package(srell MODULE REQUIRED)

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		CommonLibF4::CommonLibF4
		Dbghelp.lib
		robin_hood::robin_hood
		spdlog::spdlog
		srell::srell
)

copy_files(
	"$<TARGET_FILE:${PROJECT_NAME}>" "Data/F4SE/Plugins/"
	"$<TARGET_PDB_FILE:${PROJECT_NAME}>" "Data/F4SE/Plugins/"
)
