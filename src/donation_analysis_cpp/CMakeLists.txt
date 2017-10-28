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

