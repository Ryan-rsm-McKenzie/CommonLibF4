cmake_minimum_required(VERSION 3.21)

project(
	CommonLibF4
	LANGUAGES CXX
)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

find_package(Boost MODULE REQUIRED)
find_package(mmio REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

include("cmake/sourcelist.cmake")

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES
		${SOURCES}
)

include(GNUInstallDirs)

add_library(
	"${PROJECT_NAME}"
	STATIC
	${SOURCES}
	"../.clang-format"
	"CommonLibF4.natvis"
)

add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

if(MSVC)
	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			"/permissive-"	# Standards conformance

			# disable warnings
			"/wd4200" # nonstandard extension used : zero-sized array in struct/union
			"/wd4201"	# nonstandard extension used : nameless struct/union
			"/wd4324" # 'struct_name' : structure was padded due to __declspec(align())

		PRIVATE
			# warnings -> errors
			"/we4715"	# 'function' : not all control paths return a value

			# disable warnings
			"/wd4061" # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
			"/wd4263" # 'function' : member function does not override any base class virtual member function
			"/wd4264" # 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden
			"/wd4266" # 'function' : no override available for virtual member function from base 'type'; function is hidden
			"/wd4371" # 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
			"/wd4514" # 'function' : unreferenced inline function has been removed
			"/wd4582" # 'type': constructor is not implicitly called
			"/wd4583" # 'type': destructor is not implicitly called
			"/wd4623" # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
			"/wd4625" # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
			"/wd4626" # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
			"/wd4686" # 'user-defined type' : possible change in behavior, change in UDT return calling convention
			"/wd4820" # 'bytes' bytes padding added after construct 'member_name'
			"/wd5027" # 'type': move assignment operator was implicitly defined as deleted
			"/wd5045" # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
			"/wd5053" # support for 'explicit(<expr>)' in C++17 and earlier is a vendor extension
			"/wd5204" # 'type-name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
			"/wd5220" # 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial
	)
endif()

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
		BOOST_STL_INTERFACES_DISABLE_CONCEPTS
		WINVER=0x0601	# windows 7, minimum supported version by fallout 4
		_WIN32_WINNT=0x0601
)

target_compile_features(
	"${PROJECT_NAME}"
	PUBLIC
		cxx_std_20
)

target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		Boost::headers
		mmio::mmio
		spdlog::spdlog
		Version.lib
)

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		"include/F4SE/Impl/PCH.h"
)

install(
	TARGETS "${PROJECT_NAME}"
	EXPORT "${PROJECT_NAME}-targets"
)

install(
	EXPORT "${PROJECT_NAME}-targets"
	NAMESPACE "${PROJECT_NAME}::"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

configure_file(
	"cmake/config.cmake.in"
	"${PROJECT_NAME}Config.cmake"
	@ONLY
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install(
	DIRECTORY
		"include/F4SE"
		"include/RE"
		"include/REL"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
