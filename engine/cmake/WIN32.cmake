    if(NOT DEFINED SDL2_DIR)
        set(SDL2_DIR "C:/SDL2")
    endif()

    if(NOT DEFINED SDL2_IMAGE_DIR)
        set(SDL2_IMAGE_DIR "C:/SDL2_image")
    endif(NOT DEFINED SDL2_IMAGE_DIR)

    if(NOT DEFINED SDL2_MIXER_DIR)
        set(SDL2_MIXER_DIR "C:/SDL2_mixer")
    endif(NOT DEFINED SDL2_MIXER_DIR)

    if(NOT DEFINED box2d_DIR)
        set(box2d_DIR "C:/box2d")
    endif(NOT DEFINED box2d_DIR)

    if(NOT DEFINED SDL2_TTF_DIR)
        set(SDL2_TTF_DIR "C:/SDL2_ttf")
    endif(NOT DEFINED SDL2_TTF_DIR)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)
    find_package(SDL2_MIXER REQUIRED)
    find_package(SDL2_TTF REQUIRED)
    find_package(box2d REQUIRED)

    include(FetchContent)
    FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
    FetchContent_MakeAvailable(json)

    set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
    target_link_libraries(engine PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${BOX2D_LIBRARIES} ${SDL2_TTF_LIBRARIES})
