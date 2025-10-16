cmake_minimum_required(VERSION 3.10)
project(BST_Tests)

add_executable(runTests test_BinarySearchTree.cpp)
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
