macro(set_from_environment VARIABLE)
	if(NOT DEFINED "${VARIABLE}" AND DEFINED "ENV{${VARIABLE}}")
		set("${VARIABLE}" "$ENV{${VARIABLE}}")
	endif()
endmacro()

macro(add_project)
	set(_PREFIX add_project)

	set(_OPTIONS)
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
		"${_PREFIX}"
		"${_OPTIONS}"
		"${_ONE_VALUE_ARGS}"
		"${_MULTI_VALUE_ARGS}"
		"${ARGN}"
	)

	foreach(_ARG ${_REQUIRED})
		if(NOT DEFINED "${_PREFIX}_${_ARG}")
			message(FATAL_ERROR "Argument is required to be defined: ${_ARG}")
		endif()
	endforeach()

	set(_CLEANUP
		_PREFIX
		_OPTIONS
		_ONE_VALUE_ARGS
		_MULTI_VALUE_ARGS
		_REQUIRED
		${_PREFIX}_UNPARSED_ARGUMENTS
		${_PREFIX}_KEYWORDS_MISSING_VALUES
	)

	foreach(_ARG IN LISTS _OPTIONS _ONE_VALUE_ARGS _MULTI_VALUE_ARGS)
		list(APPEND _CLEANUP "${_PREFIX}_${_ARG}")
	endforeach()

	# ---- Argument validation

	string(TOLOWER "${${_PREFIX}_TARGET_TYPE}" "${_PREFIX}_TARGET_TYPE")

	if(DEFINED "${_PREFIX}_UNPARSED_ARGUMENTS")
		foreach(_ARG "${_PREFIX}_UNPARSED_ARGUMENTS")
			message(WARNING "Unused argument: ${_ARG}")
		endforeach()
	endif()

	set(_TARGET_TYPES executable library)
	list(APPEND _CLEANUP _TARGET_TYPES)
	if(NOT "${${_PREFIX}_TARGET_TYPE}" IN_LIST _TARGET_TYPES)
		message(FATAL_ERROR "TARGET_TYPE \"${${_PREFIX}_TARGET_TYPE}\" must be one of: ${_TARGET_TYPES}")
	endif()

	set(_LIBRARY_TYPES STATIC SHARED MODULE)
	list(APPEND _CLEANUP _LIBRARY_TYPES)
	if(DEFINED "${_PREFIX}_LIBRARY_TYPE" AND
		NOT "${${_PREFIX}_LIBRARY_TYPE}" IN_LIST _LIBRARY_TYPES)
		message(FATAL_ERROR "LIBRARY_TYPE \"${${_PREFIX}_LIBRARY_TYPE}\" must be one of: ${_LIBRARY_TYPES}")
	endif()

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
		list(APPEND _CLEANUP _VERSION_PREFIX)
	else()
		unset(_VERSION_PREFIX)
	endif()

	project(
		"${${_PREFIX}_PROJECT}"
		${_VERSION_PREFIX} ${${_PREFIX}_VERSION}
		LANGUAGES CXX
	)

	# ---- Include guards ----

	if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
		message(FATAL_ERROR "in-source builds are not allowed")
	endif()

	# ---- Add target ----

	cmake_language(
		CALL
		"add_${${_PREFIX}_TARGET_TYPE}"	# add_executable/add_library
		"${PROJECT_NAME}"
		"${${_PREFIX}_LIBRARY_TYPE}"
		${${_PREFIX}_GROUPED_FILES}
		${${_PREFIX}_MISC_FILES}
	)

	set_target_properties(
		"${PROJECT_NAME}"
		PROPERTIES
			CXX_STANDARD 20
			CXX_STANDARD_REQUIRED ON
			INTERPROCEDURAL_OPTIMIZATION ON
			INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF
	)

	target_compile_definitions(
		"${PROJECT_NAME}"
		PRIVATE
			_UNICODE
			${${_PREFIX}_COMPILE_DEFINITIONS}
	)

	target_include_directories(
		"${PROJECT_NAME}"
		PRIVATE
			${${_PREFIX}_INCLUDE_DIRECTORIES}
	)

	target_precompile_headers(
		"${PROJECT_NAME}"
		PRIVATE
			${${_PREFIX}_PRECOMPILED_HEADERS}
	)

	if(MSVC)
		target_compile_options(
			"${PROJECT_NAME}"
			PRIVATE
				"/sdl"	# Enable Additional Security Checks
				"/utf-8"	# Set Source and Executable character sets to UTF-8
				"/Zi"	# Debug Information Format

				"/permissive-"	# Standards conformance
		)

		target_link_options(
			"${PROJECT_NAME}"
			PRIVATE
				/WX	# Treat Linker Warnings as Errors

				"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
				"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
		)
	endif()

	source_group(
		TREE "${CMAKE_CURRENT_SOURCE_DIR}"
		FILES
			${${_PREFIX}_GROUPED_FILES}
	)

	# ---- Cleanup local variables ----

	foreach(_VAR "${_CLEANUP}")
		unset("${_VAR}")
	endforeach()
	unset(_CLEANUP)
endmacro()

macro(copy_files)
	if(NOT "${ARGC}" GREATER 0)
		message(FATAL_ERROR "Invalid number of arguments.")
	endif()

	math(EXPR _REMAINDER "${ARGC} % 2")
	if(NOT _REMAINDER EQUAL 0)
		message(FATAL_ERROR "Arguments must be paired as a file + path spec.")
	endif()

	option(COPY_BUILD "Copy the build output to the Fallout 4 directory." OFF)

	set(_ARGS "${ARGN}")

	if(COPY_BUILD)
		set_from_environment(Fallout4Path)
		if(DEFINED Fallout4Path)
			math(EXPR _PAIRS "${ARGC} / 2 - 1")
			foreach(_IDX RANGE "${_PAIRS}")
				math(EXPR _IDX "${_IDX} * 2")
				math(EXPR _IDXN "${_IDX} + 1")

				list(GET _ARGS "${_IDX}" _FROM)
				list(GET _ARGS "${_IDXN}" _TO)

				cmake_path(SET _TO NORMALIZE "${Fallout4Path}/${_TO}")

				add_custom_command(
					TARGET "${PROJECT_NAME}"
					POST_BUILD
					COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${_FROM}" "${_TO}"
				)
			endforeach()
		else()
			message(WARNING "Variable Fallout4Path is not defined. Skipping post-build copy command.")
		endif()
	endif()

	unset(_ARGS)
	unset(_REMAINDER)
	unset(_IDX)
	unset(_IDXN)
	unset(_FROM)
	unset(_TO)
endmacro()
