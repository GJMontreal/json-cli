cmake_minimum_required(VERSION 3.10)
project(json_reader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(json_reader main.cpp)

target_include_directories(json_reader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external)
