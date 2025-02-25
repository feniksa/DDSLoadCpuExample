cmake_minimum_required(VERSION 3.30)
project(dssloader)

set(CMAKE_CXX_STANDARD 23)

find_package(directxtex CONFIG REQUIRED)

add_executable(dssloader main.cpp)
target_link_libraries(dssloader PRIVATE Microsoft::DirectXTex)