cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# ---- Project ----

project(
	CommonLibF4
	VERSION 1.0.0
	LANGUAGES CXX
)

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

# ---- Create library ----

add_library(CommonLibF4 ${headers} ${sources})

target_include_directories(
	CommonLibF4
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>    
)

target_compile_features(CommonLibF4 PRIVATE cxx_std_17)
target_compile_options(CommonLibF4
	PUBLIC 
		"$<$<BOOL:${MSVC}>:
			/experimental:external
			/external:anglebrackets
			/external:W0
			/Zc:alignedNew
			/Zc:auto
			/Zc:char8_t
			/Zc:__cplusplus
			/Zc:externC
			/Zc:externConstexpr
			/Zc:forScope
			/Zc:hiddenFriend
			/Zc:implicitNoexcept
			/Zc:lambda
			/Zc:noexceptTypes
			/Zc:preprocessor
			/Zc:referenceBinding
			/Zc:rvalueCast
			/Zc:sizedDealloc
			/Zc:strictStrings
			/Zc:ternary
			/Zc:threadSafeInit
			/Zc:tlsGuards
			/Zc:trigraphs
			/Zc:wchar_t
		>"
)

target_link_libraries(CommonLibF4
	PUBLIC
		Boost::atomic
		Boost::headers
		Boost::iostreams
		nonstd::span-lite
		spdlog::spdlog
)
