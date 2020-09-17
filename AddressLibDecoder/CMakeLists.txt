cmake_minimum_required(VERSION 3.18)

# ---- Project ----

project(
	AddressLibDecoder
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

set(MSVC_OPTIONS_GLOBAL
	/MP	# Build with Multiple Processes
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

add_compile_definitions(
	"$<$<BOOL:${MSVC}>:_UNICODE>"
)

add_compile_options(
	"$<$<BOOL:${MSVC}>:${MSVC_OPTIONS_GLOBAL}>"
)

# ---- Dependencies ----

find_package(Boost
	REQUIRED
	COMPONENTS
		filesystem
		iostreams
)
find_package(fmt REQUIRED)
find_package(span-lite REQUIRED)

# ---- Add source files ----

set(sources
	src/main.cpp
)

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${sources}
)

# ---- Create Executable ----

set(MSVC_OPTIONS_PRIVATE
	/TP	# Specify Source File Type (C++)
)

add_executable(AddressLibDecoder
	${sources}
	.clang-format
)

target_compile_features(AddressLibDecoder
	PUBLIC
		cxx_std_17
)

target_compile_options(AddressLibDecoder
	PRIVATE
		"$<$<BOOL:${MSVC}>:${MSVC_OPTIONS_PRIVATE}>"
)

target_include_directories(AddressLibDecoder
	PRIVATE 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:src>
)

target_link_libraries(AddressLibDecoder
	PUBLIC
		Boost::filesystem
		Boost::iostreams
		fmt::fmt
		nonstd::span-lite
)

target_link_options(AddressLibDecoder
	PUBLIC
		"$<$<AND:$<BOOL:${MSVC}>,$<CONFIG:RELEASE>>:/DEBUG:FULL>"
)
