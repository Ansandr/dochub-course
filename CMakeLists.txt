cmake_minimum_required(VERSION 3.10)
project(dochub VERSION 0.1.0 LANGUAGES C CXX)

# Collect all source files in the src directory
file(GLOB_RECURSE PROJECT_SRC src/*.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dochub
    app/main.cpp
    ${PROJECT_SRC}
)