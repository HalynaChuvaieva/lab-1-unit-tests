cmake_minimum_required(VERSION 3.14)
project(MyProjectName LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2 
)
FetchContent_MakeAvailable(Catch2)



add_executable(lab-1.cpp)
target_include_directories(main PRIVATE src)



file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)