cmake_minimum_required(VERSION 3.0)
project(test_donation_analysis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Download and unpack googletest at configure time 
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in
    ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt
)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)
                                                     
# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# donation_analysis library source code
set(MYLIBDIR
    "${CMAKE_CURRENT_SOURCE_DIR}/../donation_analysis_cpp"
)

set(mysrcs
    ${MYLIBDIR}/include/MedianInterface.h
    ${MYLIBDIR}/include/MedianRunning.h
    ${MYLIBDIR}/include/MedianStatic.h
    ${MYLIBDIR}/include/TrackerInterface.h
    ${MYLIBDIR}/include/TrackerZip.h
    ${MYLIBDIR}/include/TrackerDate.h
    ${MYLIBDIR}/include/Record.h
    ${MYLIBDIR}/src/MedianRunning.cpp
    ${MYLIBDIR}/src/MedianStatic.cpp
    ${MYLIBDIR}/src/TrackerZip.cpp
    ${MYLIBDIR}/src/TrackerDate.cpp
    ${MYLIBDIR}/src/Record.cpp
)

# test cases
set(srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/testMedian.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/testTracker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/testRecord.cpp
)

get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
#set(CMAKE_PREFIX_PATH
#    ${PARENT_DIR}/cpp_impl/lib/cmake
#    )

# import library target `donation_analysis`
#find_package(donation_analysis CONFIG REQUIRED)

add_executable(runUnitTests ${srcs} ${mysrcs})
include_directories( 
    ${PARENT_DIR}/donation_analysis_cpp/include
)
target_link_libraries(runUnitTests gtest_main)
add_test(runUnitTests srcs)


