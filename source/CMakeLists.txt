cmake_minimum_required(VERSION 3.17)
project(source)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all -Wall -Wextra"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

add_subdirectory(banks_lib)

add_executable(banks main.cpp)
target_link_libraries(banks PUBLIC BanksLibrary)
