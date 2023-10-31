cmake_minimum_required(VERSION 3.26)
project(slime_shooter)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(-Wall -Wpedantic)
add_compile_options("$<$<CONFIG:DEBUG>:-g>")

add_executable(slime_shooter main.cc
        test_scene.h
        movement_script.h
)

target_include_directories(slime_shooter PRIVATE src)

target_compile_features(slime_shooter PUBLIC cxx_std_17)
target_link_libraries(slime_shooter PRIVATE engine)

add_custom_target(game-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")