cmake_minimum_required(VERSION 3.23)
project(Krypton)

set(CMAKE_CXX_STANDARD 20)

add_executable(Krypton encrypt.cpp decrypt.cpp main.cpp header.hpp)
