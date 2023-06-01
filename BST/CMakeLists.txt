cmake_minimum_required(VERSION 3.24)
project(BST)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BST
        Binary_Search_Tree.cpp
        Binary_Search_Tree.h)
