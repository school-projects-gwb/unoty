cmake_minimum_required(VERSION 3.22)
project(unoty)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2")
    set(SDL2_IMAGE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2_image")
    set(SDL2_MIXER_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2_mixer")
    set(SDL2_TTF_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2_ttf")
    set(box2d_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/box2d")

    find_package(SDL2 REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)
    find_package(SDL2_MIXER REQUIRED)
    find_package(SDL2_TTF REQUIRED)
    find_package(box2d REQUIRED)
endif(WIN32)

set(INSTALL_DIR ${PROJECT_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${INSTALL_DIR})

add_subdirectory(engine)
add_subdirectory(slime_shooter)
add_subdirectory(engine_tests)

if(WIN32)
    list(GET SDL2_LIBRARIES 0 HEAD_SDL2_LIBRARIES)
    get_filename_component(SDL2_DLL_DIR ${HEAD_SDL2_LIBRARIES} DIRECTORY CACHE)

    list(GET SDL2_IMAGE_LIBRARIES 0 HEAD_SDL2_IMAGE_LIBRARIES)
    get_filename_component(SDL2_IMAGE_DLL_DIR ${HEAD_SDL2_IMAGE_LIBRARIES} DIRECTORY CACHE)

    list(GET SDL2_MIXER_LIBRARIES 0 HEAD_SDL2_MIXER_LIBRARIES)
    get_filename_component(SDL2_MIXER_DLL_DIR ${HEAD_SDL2_MIXER_LIBRARIES} DIRECTORY CACHE)

    list(GET BOX2D_LIBRARIES 0 HEAD_BOX2D_LIBRARIES)
    get_filename_component(BOX2D_DLL_DIR ${HEAD_BOX2D_LIBRARIES} DIRECTORY)

    list(GET SDL2_TTF_LIBRARIES 0 HEAD_SDL2_TTF_LIBRARIES)
    get_filename_component(SDL2_TTF_DLL_DIR ${HEAD_SDL2_TTF_LIBRARIES} DIRECTORY)

    file(GLOB SDL2_DLLS "${SDL2_DLL_DIR}/*.dll")
    file(GLOB SDL2_IMAGE_DLLS "${SDL2_IMAGE_DLL_DIR}/*.dll")
    file(GLOB SDL2_MIXER_DLLS "${SDL2_MIXER_DLL_DIR}/*.dll")
    file(GLOB SDL2_TTF_DLLS "${SDL2_TTF_DLL_DIR}/*.dll")
    file(GLOB BOX2D_DLLS "${BOX2D_DLL_DIR}/*.dll")

    add_custom_target(dependencies ALL
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DLLS} ${SDL2_IMAGE_DLLS} ${SDL2_MIXER_DLLS} ${SDL2_TTF_DLLS} ${BOX2D_DLLS} ${INSTALL_DIR})
endif(WIN32)