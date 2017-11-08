cmake_minimum_required(VERSION 3.8)
project(zbp_bst)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp binary_search_tree.h)
add_executable(zbp_bst ${SOURCE_FILES})