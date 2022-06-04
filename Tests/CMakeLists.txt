add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT Tests
	COMPILE_DEFINITIONS
		F4SE_TEST_SUITE
	INCLUDE_DIRECTORIES
		"../CommonLibF4/include"
		src
	GROUPED_FILES
		"src/BSTHashMap.cpp"
		"src/pch.h"
	PRECOMPILED_HEADERS
		"src/pch.h"
)

find_package(Boost MODULE REQUIRED)
find_package(Catch2 REQUIRED CONFIG)

include(Catch)
catch_discover_tests("${PROJECT_NAME}")

target_compile_definitions(
	"${PROJECT_NAME}"
	PRIVATE
		BOOST_STL_INTERFACES_DISABLE_CONCEPTS
)

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		Boost::headers
		Catch2::Catch2WithMain
)
