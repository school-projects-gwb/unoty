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
        include/*.h include/*/*.h include/*/*/*.h
        include/engine/engine.h
        include/engine/engine_config.h
        include/engine/physics.h
        include/engine/renderer.h

        include/entities/artificial_intelligence/artificial_intelligence.h
        include/entities/artificial_intelligence/player_turret.h

        include/entities/colliders/collider.h
        include/entities/colliders/circle_collider.h
        include/entities/colliders/box_collider.h

        include/entities/listeners/key_listener.h
        include/entities/listeners/mouse_listener.h

        include/entities/structs/color.h
        include/entities/structs/key.h
        include/entities/structs/point.h
        include/entities/structs/button.h
        include/entities/structs/text.h
        include/entities/structs/ui_object.h

        include/entities/animator.h
        include/entities/audio_source.h
        include/entities/behaviour_script.h
        include/entities/camera.h
        include/entities/component.h
        include/entities/game_object.h
        include/entities/rigid_body.h
        include/entities/scene.h
        include/entities/scene_callback_function.h
        include/entities/sprite.h
        include/entities/transform.h
        include/helpers/path_helper.h

        src/audio/audio.cc
        src/audio/audio.h
        src/engine/engine.cc

        src/engine/engine_tick.cc
        src/engine/engine_tick.h
        src/engine/scene_manager.cc
        src/engine/scene_manager.h

        src/entities/artificial_intelligence/player_turret.cc
        src/entities/colliders/box_collider.cc
        src/entities/colliders/circle_collider.cc

        src/entities/animator.cc
        src/entities/behaviour_script.cc
        src/entities/camera.cc
        src/entities/game_object.cc
        src/entities/scene.cc
        src/entities/sprite.cc
        src/entities/transform.cc

        src/input/input.h
        src/input/sdl_input.cc
        src/input/sdl_input.h

        src/physics/impl_physics.cc
        src/physics/impl_physics.h

        src/rendering/textures/sdl_texture_registry.cc
        src/rendering/textures/sdl_texture_registry.h
        src/rendering/textures/texture_registry.h
        src/rendering/textures/texture_registry_base.h

        src/rendering/sdl_renderer.cc
        src/rendering/sdl_renderer.h
)

add_library(engine SHARED ${SOURCES})

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
