cmake_minimum_required(VERSION 3.7)
project(cpp_vector)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_vector main.cpp vector.hpp catch.hpp)
add_executable(catch_tests catch_tests.cpp vector.hpp catch.hpp)