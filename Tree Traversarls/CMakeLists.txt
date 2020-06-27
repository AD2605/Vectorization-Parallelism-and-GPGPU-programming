cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Tree_Traversals)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tree_Traversals main.cpp)
target_compile_options(Tree_Traversals PUBLIC "-fopenmp")
