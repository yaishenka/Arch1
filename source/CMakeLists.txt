cmake_minimum_required(VERSION 3.17)
project(source)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(banks_lib)


add_executable(main main.cpp)
target_link_libraries(main PUBLIC BanksLibrary)
target_include_directories(main PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/banks_lib>)