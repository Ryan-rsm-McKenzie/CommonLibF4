add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT f4se_loader
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		"src/main.cpp"
		"src/PCH.h"
	PRECOMPILED_HEADERS
		"src/PCH.h"
)

find_package(args REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(frozen REQUIRED CONFIG)
find_package(nowide REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)
find_package(xbyak REQUIRED CONFIG)

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		fmt::fmt
		frozen::frozen
		nowide::nowide
		spdlog::spdlog
		taywee::args
		Version.lib
		xbyak::xbyak
)

copy_files(
	"$<TARGET_FILE:${PROJECT_NAME}>" "/"
	"$<TARGET_PDB_FILE:${PROJECT_NAME}>" "/"
)
