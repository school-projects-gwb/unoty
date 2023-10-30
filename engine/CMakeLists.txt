cmake_minimum_required(VERSION 3.26)
project(engine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
        src/*.cc src/*.h src/*/*.cc src/*/*.h src/*/*/*.h
        include/*.h include/*/*.h include/*/*/*.h
)

add_library(engine ${SOURCES})

target_include_directories(engine PUBLIC include/)

# SDL2
if (WIN32)
    set(SDL2_DIR "C:/Program Files/SDL/SDL2/cmake")
    set(SDL2_image_DIR "C:/Program Files/SDL/SDL2_image/cmake")
endif (WIN32)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
