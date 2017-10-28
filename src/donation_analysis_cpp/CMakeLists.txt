cmake_minimum_required(VERSION 3.0)
project(donation_analysis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(donation_analysis SHARED "")
target_include_directories(donation_analysis
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
    )

include("include/CMakeLists.txt")
include("src/CMakeLists.txt")

get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

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
        include/Record.h
        include/Tracker.h
    DESTINATION
        include
)

install(
    FILES 
        donation_analysis-config.cmake 
    DESTINATION 
        lib/cmake/
)

