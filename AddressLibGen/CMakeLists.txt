cmake_minimum_required(VERSION 3.18)

# ---- Project ----

cmake_policy(SET CMP0091 NEW)	# MSVC runtime library flags are selected by an abstraction

project(
	AddressLibGen
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

# ---- Globals ----

set(MSVC_COMPILE_OPTIONS
	/Gy	# Enable Function-Level Linking
	/MP	# Build with Multiple Processes
	/Oi	# Generate Intrinsic Functions
	/sdl	# Enable Additional Security Checks
	/Zi	# Debug Information Format
	
	/permissive-	# Standards conformance
	
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
	
	/experimental:external
	/external:anglebrackets
	/external:W0
	
	/W4	# Warning level (all warnings)
	/WX	# Warning level (warnings are errors)
)

set(MSVC_COMPILE_OPTIONS_DEBUG
	/Zc:inline-	# Keep unreferenced COMDAT
	/JMC	# Just My Code debugging
)

set(MSVC_COMPILE_OPTIONS_RELEASE
	/Zc:inline	# Remove unreferenced COMDAT
	/JMC-	# Disable Just My Code debugging
)

set(MSVC_LINK_OPTIONS_DEBUG
	/INCREMENTAL	# Link Incrementally
	/OPT:NOREF	# Optimizations (keep functions/data never referenced)
	/OPT:NOICF	# Optimizations (prevent identical COMDAT folding)
)

set(MSVC_LINK_OPTIONS_RELEASE
	/INCREMENTAL:NO	# Link Incrementally
	/OPT:REF	# Optimizations (eliminate functions/data never referenced)
	/OPT:ICF	# Optimizations (perform identical COMDAT folding)
)

add_compile_definitions(
	"$<$<BOOL:${MSVC}>:_UNICODE>"
	TOML_WINDOWS_COMPAT=0
)

add_compile_options(
	"$<$<BOOL:${MSVC}>:${MSVC_COMPILE_OPTIONS}>"
	"$<$<AND:$<BOOL:${MSVC}>,$<CONFIG:DEBUG>>:${MSVC_COMPILE_OPTIONS_DEBUG}>"
	"$<$<AND:$<BOOL:${MSVC}>,$<CONFIG:RELEASE>>:${MSVC_COMPILE_OPTIONS_RELEASE}>"
)

add_link_options(
	"$<$<AND:$<BOOL:${MSVC}>,$<CONFIG:DEBUG>>:${MSVC_LINK_OPTIONS_DEBUG}>"
	"$<$<AND:$<BOOL:${MSVC}>,$<CONFIG:RELEASE>>:${MSVC_LINK_OPTIONS_RELEASE}>"
)

# ---- Dependencies ----

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_USE_DEBUG_RUNTIME ON)

find_package(Boost
	REQUIRED
	COMPONENTS
		regex
)

find_path(ROBIN_HOOD_HASHING_INCLUDE_DIRS "robin_hood.h" REQUIRED)	# TODO: fix port

# ---- Add source files ----

set(sources
	src/main.cpp
)

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${sources}
)

# ---- Create Executable ----

add_executable(AddressLibGen
	${sources}
	.clang-format
)

set_property(
	TARGET AddressLibGen
	PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

target_compile_features(AddressLibGen
	PUBLIC
		cxx_std_17
)

target_compile_options(AddressLibGen
	PRIVATE
		"$<$<BOOL:${MSVC}>:/TP>"
)

target_include_directories(AddressLibGen
	PRIVATE 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:src>
		${ROBIN_HOOD_HASHING_INCLUDE_DIRS}
)

target_link_libraries(AddressLibGen
	PUBLIC
		Boost::regex
)

target_link_options(AddressLibGen
	PUBLIC
		"$<$<AND:$<BOOL:${MSVC}>,$<CONFIG:RELEASE>>:/DEBUG:FULL>"
)
