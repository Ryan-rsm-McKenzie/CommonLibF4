cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# ---- Project ----

project(
	CommonLibF4
	VERSION 1.0.0
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

find_package(Boost
	REQUIRED
	COMPONENTS
		atomic
		iostreams
)
find_package(span-lite REQUIRED)
find_package(spdlog REQUIRED)

# ---- Add source files ----

include(headerlist.cmake)
include(sourcelist.cmake)

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${headers} ${sources}
)

# ---- Create library ----

add_library(CommonLibF4 ${headers} ${sources})

set(MSVC_OPTIONS_PUBLIC
	/permissive-	# Standards conformance

	/experimental:external
	/external:anglebrackets
	/external:W0
	
	/MP	# Build with Multiple Processes
	/TP	# Specify Source File Type (C++)
	
	/Zc:alignedNew	# C++17 over-aligned allocation
	/Zc:auto	# Deduce Variable Type
	/Zc:char8_t
	/Zc:__cplusplus	# Enable updated __cplusplus macro
	/Zc:externC
	/Zc:externConstexpr	# Enable extern constexpr variables
	/Zc:forScope	# Force Conformance in for Loop Scope
	/Zc:hiddenFriend
	/Zc:implicitNoexcept	# Implicit Exception Specifiers
	/Zc:lambda
	/Zc:noexceptTypes	# C++17 noexcept rules
	/Zc:preprocessor	# Enable preprocessor conformance mode
	/Zc:referenceBinding	# Enforce reference binding rules
	/Zc:rvalueCast	# Enforce type conversion rules
	/Zc:sizedDealloc	# Enable Global Sized Deallocation Functions
	/Zc:strictStrings	# Disable string literal type conversion
	/Zc:ternary	# Enforce conditional operator rules
	/Zc:threadSafeInit	# Thread-safe Local Static Initialization
	/Zc:tlsGuards
	/Zc:trigraphs	# Trigraphs Substitution
	/Zc:wchar_t	# wchar_t Is Native Type
)

set(MSVC_OPTIONS_PRIVATE
	/Wall	# Warning level (all warnings)
	/WX	# Warning level (warnings are errors)
	
	# warnings -> errors
	/we4715	# 'function' : not all control paths return a value
	
	# disable warnings
	/wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
	/wd4200 # nonstandard extension used : zero-sized array in struct/union
	/wd4263 # 'function' : member function does not override any base class virtual member function
	/wd4264 # 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden
	/wd4266 # 'function' : no override available for virtual member function from base 'type'; function is hidden
	/wd4324 # 'struct_name' : structure was padded due to __declspec(align())
	/wd4371 # 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
	/wd4514 # 'function' : unreferenced inline function has been removed
	/wd4582 # 'type': constructor is not implicitly called
	/wd4583 # 'type': destructor is not implicitly called
	/wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
	/wd4625 # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
	/wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
	/wd4686 # 'user-defined type' : possible change in behavior, change in UDT return calling convention
	/wd4820 # 'bytes' bytes padding added after construct 'member_name'
	/wd5027 # 'type': move assignment operator was implicitly defined as deleted
	/wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
	/wd5053 # support for 'explicit(<expr>)' in C++17 and earlier is a vendor extension
	/wd5204 # 'type-name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
	/wd5220 # 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial
)

target_compile_features(CommonLibF4 PRIVATE cxx_std_17)
target_compile_options(CommonLibF4
	PUBLIC
		"$<$<BOOL:${MSVC}>:${MSVC_OPTIONS_PUBLIC}>"
	PRIVATE
		"$<$<BOOL:${MSVC}>:${MSVC_OPTIONS_PRIVATE}>"
)

target_include_directories(
	CommonLibF4
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>    
)

target_link_libraries(CommonLibF4
	PUBLIC
		Boost::atomic
		Boost::headers
		Boost::iostreams
		nonstd::span-lite
		spdlog::spdlog
)

target_precompile_headers(CommonLibF4
	PRIVATE include/F4SE/Impl/PCH.h
)
