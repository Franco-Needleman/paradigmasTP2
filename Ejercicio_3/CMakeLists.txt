cmake_minimum_required(VERSION 3.10)
project(Ejercicio2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ejercicio3 main3.cpp)

target_compile_options(ejercicio3 PRIVATE -Wall -Wextra -Wpedantic) 