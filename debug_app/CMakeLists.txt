cmake_minimum_required(VERSION 3.26)
project(debug_app)

set(CMAKE_CXX_STANDARD 17)

add_executable(debug_app main.cc
        test_scene.h)

target_link_libraries(debug_app PRIVATE engine)
include_directories(../engine/include)
target_link_directories(debug_app PRIVATE ../engine/cmake-build-debug)
