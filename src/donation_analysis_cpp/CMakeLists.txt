cmake_minimum_required(VERSION 3.0)
project(donation_analysis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(FIND_POLITICAL_DONORS "build executable for find_political_donor tests" ON)
option(INDEPENDENT_LIB "build an independent library" OFF)

get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
get_filename_component(ROOT_PARENT_DIR ${PARENT_DIR} DIRECTORY)

set(MY_DEFAULT_OPTIONS -O3 -std=c++14 -Wall -Werror -Wextra -pedantic)
    
# Generate executable for testing
if(FIND_POLITICAL_DONORS)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_PARENT_DIR})
    add_executable(find_political_donors "${PROJECT_SOURCE_DIR}/main.cpp")
    target_include_directories(find_political_donors
        PUBLIC "${PROJECT_SOURCE_DIR}/include")
    target_compile_options(find_political_donors
        PUBLIC ${MY_DEFAULT_OPTIONS})
endif()

# if compile code as a independent library
if(INDEPENDENT_LIB)
    add_library(donation_analysis SHARED "")
    target_include_directories(donation_analysis
        PUBLIC "${PROJECT_SOURCE_DIR}/include"
        )
    
    target_compile_options(donation_analysis
        PUBLIC ${MY_DEFAULT_OPTIONS})

    set(CMAKE_INSTALL_PREFIX
        "${PARENT_DIR}/cpp_impl"
        )
    
    install(TARGETS donation_analysis 
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )
    install(
        FILES
            include/donation_analysis.h
            include/MedianInterface.h
            include/MedianRunning.h
            include/MedianStatic.h
            include/TrackerInterface.h
            include/TrackerZip.h
            include/TrackerDate.h
            include/Record.h
        DESTINATION
            include
    )
    
    install(
        FILES 
            donation_analysis-config.cmake 
        DESTINATION 
            lib/cmake/
    )
endif()

include("include/CMakeLists.txt")
include("src/CMakeLists.txt")

