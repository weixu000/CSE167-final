cmake_minimum_required(VERSION 3.15)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(GLEW REQUIRED)

add_subdirectory("deps")
add_subdirectory("src")