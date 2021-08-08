add_project(
	TARGET_TYPE EXECUTABLE
	PROJECT AddressLibDecoder
	VERSION 1.0.0
	INCLUDE_DIRECTORIES
		src
	GROUPED_FILES
		"src/main.cpp"
)

find_package(Boost
	MODULE
	REQUIRED
	COMPONENTS
		iostreams
)
find_package(fmt REQUIRED CONFIG)

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		Boost::iostreams
		fmt::fmt
)
