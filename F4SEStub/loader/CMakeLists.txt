cmake_minimum_required(VERSION 3.20)

include(../../cmake/common.cmake)
add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT f4se_loader
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		src/main.cpp
		src/PCH.h
		.clang-format
	PRECOMPILED_HEADERS
		src/PCH.h
)

set(Boost_USE_STATIC_LIBS ON)

find_package(args REQUIRED CONFIG)
find_package(
	Boost
	MODULE
	REQUIRED
	COMPONENTS
		nowide
)
find_package(fmt REQUIRED CONFIG)
find_package(frozen REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)
find_package(xbyak REQUIRED CONFIG)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		Boost::nowide
		fmt::fmt
		frozen::frozen
		spdlog::spdlog
		taywee::args
		Version.lib
		xbyak::xbyak
)

# ---- File copying ----

if (COPY_BUILD)
	if (DEFINED Fallout4Path)
		add_custom_command(
			TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${Fallout4Path}
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PDB_FILE:${PROJECT_NAME}> ${Fallout4Path}
		)
	else ()
		message(
			WARNING
			"Variable Fallout4Path is not defined. Skipping post-build copy command."
		)
	endif ()
endif ()
