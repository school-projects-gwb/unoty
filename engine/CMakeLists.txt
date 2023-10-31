cmake_minimum_required(VERSION 3.8)
project(engine)
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    if(NOT DEFINED SDL2_DIR)
        set(SDL2_DIR "C:/SDL2")
    endif()
    if(NOT DEFINED SDL2_IMAGE_DIR)
        set(SDL2_IMAGE_DIR "C:/SDL2_image")
    endif(NOT DEFINED SDL2_IMAGE_DIR)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)
else() # unix
    include(FindPkgConfig)
    find_package(SDL2 REQUIRED COMPONENTS SDL2)
    find_package(SDL2_IMAGE REQUIRED)
endif()

add_compile_options(-Wall -Wpedantic)
add_compile_options("$<$<CONFIG:DEBUG>:-g>")

file(GLOB_RECURSE SOURCES
        src/*.cc src/*.h src/*/*.cc src/*/*.h src/*/*/*.h
        include/*.h include/*/*.h include/*/*/*.h
)

add_library(engine SHARED ${SOURCES} include/helpers/path_helper.h)

if(WIN32)
    set_target_properties(engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
    target_link_libraries(engine PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
else()
    target_link_libraries(engine PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
endif()

target_include_directories(engine PUBLIC include)
target_include_directories(engine PRIVATE
        src
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS})

install(DIRECTORY include/engine
        DESTINATION include/engine
        FILES_MATCHING PATTERN "*.hpp")

install(TARGETS engine
        DESTINATION lib/)
