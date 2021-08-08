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

find_package(Boost
	MODULE
	REQUIRED
	COMPONENTS
		unit_test_framework
)

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		Boost::headers
		Boost::unit_test_framework
)
