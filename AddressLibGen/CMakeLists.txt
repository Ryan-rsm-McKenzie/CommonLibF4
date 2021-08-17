add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT AddressLibGen
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		"src/main.cpp"
)

find_package(ctre REQUIRED CONFIG)
find_package(robin_hood REQUIRED CONFIG)

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		ctre::ctre
		robin_hood::robin_hood
)
