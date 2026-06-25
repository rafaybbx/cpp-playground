cmake_minimum_required(VERSION 3.20)

project(cpp_playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_playground
    core/main.cpp
    core/lab_registry.cpp
    labs/initialization.cpp
)

target_include_directories(cpp_playground PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(cpp_playground PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
)
