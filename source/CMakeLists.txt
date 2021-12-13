cmake_minimum_required(VERSION 3.17)
project(source)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(banks_lib)

add_executable(banks main.cpp)
target_link_libraries(banks PUBLIC BanksLibrary)
