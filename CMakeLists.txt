cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(M1Libraries2 LANGUAGES CXX)

find_package(Catch2 3 REQUIRED)

list(APPEND _testSources Timer/test/test.cpp)

add_executable(M1Libraries2_Test ${_testSources})

target_link_libraries(M1Libraries2_Test PRIVATE Catch2::Catch2WithMain)