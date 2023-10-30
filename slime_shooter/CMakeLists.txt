cmake_minimum_required(VERSION 3.26)
project(slime_shooter)

set(CMAKE_CXX_STANDARD 17)

add_executable(slime_shooter main.cc
        test_scene.h
        movement_script.h
)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(slime_shooter PRIVATE SDL2::SDL2 SDL2_image::SDL2_image engine)

include_directories(../engine/include)
target_link_directories(slime_shooter PRIVATE ../engine/cmake-build-debug)

# Logic for copying resources to build output
set(SOURCE_RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")
set(DESTINATION_RESOURCES_DIR "${CMAKE_BINARY_DIR}/resources")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SOURCE_RESOURCES_DIR}"
        "${DESTINATION_RESOURCES_DIR}"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCES_DIR="${DESTINATION_RESOURCES_DIR}")
