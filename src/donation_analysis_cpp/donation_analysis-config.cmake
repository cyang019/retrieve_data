add_library(donation_analysis SHARED IMPORTED)

find_library(
    DONATION_ANALYSIS_LIBRARY_PATH donation_analysis
    HINTS 
    "${CMAKE_CURRENT_LIST_DIR}/../"
    )

set_target_properties(donation_analysis
    PROPERTIES
    IMPORTED_LOCATION "${DONATION_ANALYSIS_LIBRARY_PATH}"
    )

get_filename_component(MYLIB_PREFIX 
    ${DONATION_ANALYSIS_LIBRARY_PATH} DIRECTORY
)

get_filename_component(MYLIB_ROOT_PREFIX 
    ${MYLIB_PREFIX} DIRECTORY
)

set(DONATION_ANALYSIS_INCLUDE_DIRS 
    "${MYLIB_ROOT_PREFIX}/include"
)
