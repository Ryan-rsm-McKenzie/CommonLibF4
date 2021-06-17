cmake_minimum_required(VERSION 3.20)

macro(add_project)
	set(_PREFIX add_project)

	set(_OPTIONS PLACEHOLDER)
	set(_ONE_VALUE_ARGS
		LIBRARY_TYPE
		PROJECT
		TARGET_TYPE
		VERSION
	)
	set(_MULTI_VALUE_ARGS
		COMPILE_DEFINITIONS
		GROUPED_FILES
		INCLUDE_DIRECTORIES
		MISC_FILES
		PRECOMPILED_HEADERS
	)

	set(_REQUIRED
		PROJECT
		TARGET_TYPE
	)

	cmake_parse_arguments(
		${_PREFIX}
		"${_OPTIONS}"
		"${_ONE_VALUE_ARGS}"
		"${_MULTI_VALUE_ARGS}"
		${ARGN}
	)

	foreach(_ARG ${_REQUIRED})
		if(NOT DEFINED "${_PREFIX}_${_ARG}")
			message(FATAL_ERROR "Argument ${_ARG} is required to be defined")
		endif()
	endforeach()

	# ---- Argument validation

	string(TOLOWER "${${_PREFIX}_TARGET_TYPE}" "${_PREFIX}_TARGET_TYPE")

	if(DEFINED "${_PREFIX}_UNPARSED_ARGUMENTS")
		foreach(_ARG "${_PREFIX}_UNPARSED_ARGUMENTS")
			message(WARNING "Unused argument: ${_ARG}")
		endforeach()
	endif()

	set(_TARGET_TYPES executable library)
	if(NOT "${${_PREFIX}_TARGET_TYPE}" IN_LIST _TARGET_TYPES)
		message(FATAL_ERROR "TARGET_TYPE \"${${_PREFIX}_TARGET_TYPE}\" must be one of: ${_TARGET_TYPES}")
	endif()
	unset(_TARGET_TYPES)

	set(_LIBRARY_TYPES STATIC SHARED MODULE)
	if(DEFINED "${_PREFIX}_LIBRARY_TYPE" AND
		NOT "${${_PREFIX}_LIBRARY_TYPE}" IN_LIST _LIBRARY_TYPES)
		message(FATAL_ERROR "LIBRARY_TYPE \"${${_PREFIX}_LIBRARY_TYPE}\" must be one of: ${_LIBRARY_TYPES}")
	endif()
	unset(_LIBRARY_TYPES)

	if("${_PREFIX}_TARGET_TYPE" STREQUAL "library" AND
		NOT DEFINED "${_PREFIX}_LIBRARY_TYPE")
		message(FATAL_ERROR "LIBRARY_TYPE must be set for \"library\" targets")
	elseif("${_PREFIX}_TARGET_TYPE" STREQUAL "executable" AND
		DEFINED "${_PREFIX}_LIBRARY_TYPE")
		message(FATAL_ERROR "LIBRARY_TYPE must not be set for \"executable\" targets")
	endif()

	# ---- Project ----

	if(DEFINED "${_PREFIX}_VERSION")
		set(_VERSION_PREFIX "VERSION")
	endif()

	project(
		"${${_PREFIX}_PROJECT}"
		${_VERSION_PREFIX} ${${_PREFIX}_VERSION}
		LANGUAGES CXX
	)

	unset(_VERSION_PREFIX)

	# ---- Include guards ----

	if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
		message(
			FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
		)
	endif()

	# ---- Add target ----

	cmake_language(
		CALL
		"add_${${_PREFIX}_TARGET_TYPE}"	# add_executable/add_library
		${PROJECT_NAME}
		"${${_PREFIX}_LIBRARY_TYPE}"
		${${_PREFIX}_GROUPED_FILES}
		${${_PREFIX}_MISC_FILES}
	)

	set_target_properties(
		${PROJECT_NAME}
		PROPERTIES
			CXX_STANDARD 20
			CXX_STANDARD_REQUIRED ON
			INTERPROCEDURAL_OPTIMIZATION ON
			INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF
	)

	target_compile_definitions(
		${PROJECT_NAME}
		PRIVATE
			_UNICODE
			${${_PREFIX}_COMPILE_DEFINITIONS}
	)

	target_include_directories(
		${PROJECT_NAME}
		PRIVATE
			${${_PREFIX}_INCLUDE_DIRECTORIES}
	)

	target_precompile_headers(
		${PROJECT_NAME}
		PRIVATE
			${${_PREFIX}_PRECOMPILED_HEADERS}
	)

	if(MSVC)
		target_compile_options(
			${PROJECT_NAME}
			PRIVATE
				/sdl	# Enable Additional Security Checks
				/utf-8	# Set Source and Executable character sets to UTF-8
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

				/external:anglebrackets
				/external:W0

				/W4	# Warning level
				/WX	# Warning level (warnings are errors)
		)

		target_link_options(
			${PROJECT_NAME}
			PRIVATE
				/WX	# Treat Linker Warnings as Errors

				"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
				"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
		)

		if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
			target_compile_options(
				${PROJECT_NAME}
				PRIVATE
					/MP	# Build with Multiple Processes
			)
		endif()
	endif()

	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${${_PREFIX}_GROUPED_FILES}
	)

	# ---- Cleanup local variables ----

	foreach(_ARG IN LISTS _OPTIONS _ONE_VALUE_ARGS _MULTI_VALUE_ARGS)
		unset("${_PREFIX}_${_ARG}")
	endforeach()

	unset(_OPTIONS)
	unset(_ONE_VALUE_ARGS)
	unset(_MULTI_VALUE_ARGS)
	unset(_REQUIRED)
	unset(_PREFIX)
endmacro()
