cmake_minimum_required(VERSION 3.17)

# ---- Project ----

project(
	stl_interfaces
	VERSION 1.74.0
	LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(
		FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
)
endif()

# ---- Dependencies ----

find_package(Boost REQUIRED)

# ---- Create library ----

include(GNUInstallDirs)

add_library(stl_interfaces INTERFACE)

target_include_directories(
	${PROJECT_NAME}
	INTERFACE
		$<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(
	${PROJECT_NAME}
	INTERFACE
		cxx_std_14
)

target_link_libraries(stl_interfaces
	INTERFACE
		Boost::headers
)

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}_Targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	"${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMinorVersion
)

configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	INSTALL_DESTINATION
	${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(
	EXPORT ${PROJECT_NAME}_Targets
	FILE ${PROJECT_NAME}Targets.cmake
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(
	FILES
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/boost
	DESTINATION include
)
