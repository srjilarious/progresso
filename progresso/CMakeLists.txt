cmake_minimum_required(VERSION 3.10)
project(progresso CXX)
set (CMAKE_CXX_STANDARD 17)

add_library(
    progresso
    src/progresso.cpp
)

target_include_directories(progresso PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
