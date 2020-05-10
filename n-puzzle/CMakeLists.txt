cmake_minimum_required(VERSION 3.0)

enable_language(CXX)

project(n_puzzle 
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(n_puzzle_exe
    ${CMAKE_SOURCE_DIR}/main.cpp
)