add_project(
	TARGET_TYPE LIBRARY
	LIBRARY_TYPE SHARED
	PROJECT f4se_steam_loader
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		"src/main.cpp"
		"src/PCH.h"
	PRECOMPILED_HEADERS
		"src/PCH.h"
)

find_package(fmt REQUIRED CONFIG)
find_package(nowide REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		fmt::fmt
		nowide::nowide
		spdlog::spdlog
)

copy_files(
	"$<TARGET_FILE:${PROJECT_NAME}>" "/"
	"$<TARGET_PDB_FILE:${PROJECT_NAME}>" "/"
)
