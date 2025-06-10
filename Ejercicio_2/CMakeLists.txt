cmake_minimum_required(VERSION 3.10)
project(Ejercicio2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

file(GLOB SOURCES "sources/*.cpp")

add_executable(ejercicio2 main2.cpp ${SOURCES})

target_compile_options(ejercicio2 PRIVATE -Wall -Wextra -Wpedantic) 