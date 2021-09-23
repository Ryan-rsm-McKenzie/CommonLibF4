add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT AddressLibGen
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		"src/main.cpp"
)

find_package(robin_hood REQUIRED CONFIG)
find_package(srell MODULE REQUIRED)

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		robin_hood::robin_hood
		srell::srell
)
