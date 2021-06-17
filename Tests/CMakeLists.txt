cmake_minimum_required(VERSION 3.20)

include(../cmake/common.cmake)
add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT Tests
	COMPILE_DEFINITIONS
		F4SE_TEST_SUITE
	INCLUDE_DIRECTORIES
		../CommonLibF4/include
		src
	GROUPED_FILES
		src/BSTHashMap.cpp
		src/pch.h
		.clang-format
	PRECOMPILED_HEADERS
		src/pch.h
)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost
	MODULE
	REQUIRED
	COMPONENTS
		unit_test_framework
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		Boost::headers
		Boost::unit_test_framework
)
