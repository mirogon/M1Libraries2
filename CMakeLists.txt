cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(M1Libraries2 LANGUAGES CXX)

find_package(Catch2 3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

list(APPEND _testSources src/Timer/test/test.cpp src/Random/test/test.cpp src/Logger/test/test.cpp src/Net/IPAddress_Test.cpp src/Net/SocketAddress_Test.cpp)

add_executable(M1Libraries2_Test ${_testSources})

target_link_libraries(M1Libraries2_Test PRIVATE Catch2::Catch2WithMain)
target_include_directories(M1Libraries2_Test PRIVATE include/M1)