add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT AddressLibDecoder
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		"src/main.cpp"
)

find_package(fmt REQUIRED CONFIG)
find_package(mmio REQUIRED CONFIG)

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		fmt::fmt
		mmio::mmio
)
