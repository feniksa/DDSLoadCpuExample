cmake_minimum_required(VERSION 3.30)
project(ddsloader)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(directxtex CONFIG REQUIRED)

add_subdirectory(src)
