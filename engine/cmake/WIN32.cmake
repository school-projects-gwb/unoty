set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_MIXER REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(box2d REQUIRED)

include(FetchContent)
FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        DOWNLOAD_EXTRACT_TIMESTAMP)
FetchContent_MakeAvailable(json)

set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
target_link_libraries(engine PRIVATE
        -static-libgcc
        -static-libstdc++
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${BOX2D_LIBRARIES})
