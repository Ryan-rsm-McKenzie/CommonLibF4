set(TARGET srell)

find_path("${TARGET}_INCLUDE_DIR"
	NAMES
		"srell.hpp"
		"srell_ucfdata2.hpp"
		"srell_updata.hpp"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
	"${TARGET}"
	FOUND_VAR "${TARGET}_FOUND"
	REQUIRED_VARS
		"${TARGET}_INCLUDE_DIR"
)

if("${${TARGET}_FOUND}")
	set("${TARGET}_INCLUDE_DIRS" ${${TARGET}_INCLUDE_DIR})

	if(NOT TARGET "${TARGET}::${TARGET}")
		add_library("${TARGET}::${TARGET}" INTERFACE IMPORTED)
	endif()

	set_target_properties(
		"${TARGET}::${TARGET}"
		PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${${TARGET}_INCLUDE_DIRS}"
	)
endif()
