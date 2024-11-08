cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0135 NEW)
project(engine)

set(CMAKE_CXX_STANDARD 17)

if (UNIX AND NOT APPLE)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")
endif ()

add_compile_options(-Wall -Wpedantic)
add_compile_options("$<$<CONFIG:DEBUG>:-g>")

add_library(${PROJECT_NAME} SHARED
        include/data_handler/file_handler/file_handler.h
        include/data_handler/data_object.h
        include/data_handler/serializer.h

        include/engine/engine.h
        include/engine/engine_config.h
        include/physics/physics_engine.h

        src/entities/artificial_intelligence/ai_base.h
        src/entities/artificial_intelligence/a_star_path_node.h
        include/entities/artificial_intelligence/circle_path_around_object_ai.h
        src/entities/artificial_intelligence/circle_path_around_object_ai.cc
        include/entities/artificial_intelligence/find_path_to_object_ai.h
        src/entities/artificial_intelligence/find_path_to_object_ai.cc

        include/entities/physics/box_collider.h
        include/entities/physics/circle_collider.h
        include/entities/physics/collider.h
        include/entities/physics/rigid_body.h

        include/entities/listeners/key_listener.h
        include/entities/listeners/listener.h
        include/entities/listeners/mouse_listener.h

        include/entities/scene/scene.h
        include/entities/scene/scene_background.h
        include/entities/scene/scene_callback_function.h

        include/entities/structs/color.h
        include/entities/structs/element_position.h
        include/entities/structs/input.h
        include/entities/structs/key.h
        include/entities/structs/point.h
        include/entities/structs/rectangle.h
        include/entities/structs/sprite_animation_state.h
        include/entities/structs/sprite_flip.h
        include/entities/structs/element_position.h
        include/entities/structs/input.h
        include/entities/structs/vector_2d.h
        include/entities/structs/rigid_body_type.h
        include/entities/structs/physics_config.h

        include/entities/ui/ui_button.h
        include/entities/ui/ui_object.h
        include/entities/ui/ui_text.h

        include/entities/animator.h
        include/entities/audio_source.h
        include/entities/behaviour_script.h
        include/entities/camera.h
        include/entities/component.h
        include/entities/game_object.h
        include/entities/sprite.h
        include/entities/transform.h
        include/entities/particle_emitters/particle.h
        include/entities/particle_emitters/particle_emitter.h

        include/entities/ui/ui_object.h
        include/entities/ui/ui_text.h
        include/entities/ui/ui_button.h
        include/entities/ui/ui_button_callback_function.h

        include/utility/path_helper.h
        include/utility/debug.h

        include/data_handler/serializer.h
        include/data_handler/data_object.h

        src/entities/audio_source.cc
        src/audio/audio_factory.cc
        src/audio/audio_factory_wrapper.cc
        src/audio/audio_factory_base.h
        src/audio/sdl_mixer/sdl_mixer_adapter.cc
        src/audio/sdl_mixer/sdl_music_wrapper.cc
        src/audio/sdl_mixer/sdl_sound_effect_wrapper.cc
        src/audio/null_audio.h

        include/rendering/renderer.h
        include/rendering/sprite_renderer.h
        include/rendering/text_renderer.h

        src/data_handler/data_object/data_object.cc
        src/data_handler/file_handler/file_handler.cc
        src/data_handler/serializer/serializer.cc
        include/data_handler/serializer_interface.h
        src/data_handler/serializer/json/nlohmann_json_serializer.cc
        src/data_handler/data_object/builders/data_object_builder.cc

        src/engine/engine.cc
        src/engine/engine_config.cc
        src/engine/engine_tick.cc

        src/entities/physics/box_collider.cc
        src/entities/physics/circle_collider.cc
        src/physics/box2d_physics_engine.h
        src/physics/box2d_physics_engine.cc
        src/entities/physics/rigid_body.cc
        src/physics/box2d_contact_listener.h

        src/entities/listeners/key_listener.cc
        src/entities/listeners/mouse_listener.cc

        src/entities/scene/scene.cc
        src/entities/scene/scene_background.cc
        src/entities/scene/scene_object_registry.cc
        src/entities/scene/scene_manager.cc
        src/entities/scene/scene_manager.h

        src/entities/ui/ui_object.cc
        src/entities/ui/ui_text.cc
        src/entities/ui/ui_button.cc

        src/entities/audio_source.cc
        src/entities/animator.cc
        src/entities/behaviour_script.cc
        src/entities/camera.cc
        src/entities/game_object.cc
        src/entities/sprite.cc
        src/entities/transform.cc
        src/entities/particle_emitter.cc
        src/entities/particle.cc

        src/input/input.cc
        src/input/sdl_input.cc

        src/rendering/textures/sdl_texture_registry.cc
        src/rendering/renderers/sdl_renderer.cc
        src/rendering/renderers/sdl_sprite_renderer.cc
        src/rendering/renderers/sdl_text_renderer.cc
        src/rendering/fonts/sdl_font_registry.cc

        include/utility/timer.h
        include/utility/object_pool.h
        include/utility/randomizer.h
        include/entities/structs/precise_point.h
        include/entities/structs/debug_info.h
        include/entities/foresight_camera.h
        src/entities/foresight_camera.cc
        include/entities/light_source.h
        src/entities/light_source.cc
        include/entities/scene/scene_lighting.h
        src/entities/scene/scene_lighting.cc
        include/entities/structs/gamepad_button.h
        include/entities/listeners/gamepad_listener.h
        src/entities/listeners/gamepad_listener.cc
        include/entities/particle_emitters/explosion_emitter.h
        include/entities/particle_emitters/spiral_emitter.h
        include/entities/particle_emitters/firework_emitter.h
        include/entities/particle_emitters/firework_particle.h

)

if (WIN32)
    include(cmake/WIN32.cmake)
else ()
    include(FindPkgConfig)
    find_package(SDL2 REQUIRED COMPONENTS SDL2)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(box2d REQUIRED)
    find_package(nlohmann_json 3.2.0 REQUIRED)

    if (APPLE)
        target_link_libraries(${PROJECT_NAME} PRIVATE
                SDL2::SDL2
                SDL2_image::SDL2_image
                SDL2_mixer::SDL2_mixer
                SDL2_ttf::SDL2_ttf
                box2d::box2d
        )
    elseif (UNIX)
        target_link_libraries(${PROJECT_NAME} PRIVATE
                SDL2::Main
                SDL2::Image
                SDL2::Mixer
                SDL2::TTF
                box2d::box2d
        )
    endif ()
endif ()

# Link JSON library
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE
        src
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${BOX2D_INCLUDE_DIRS})

install(DIRECTORY include/engine
        DESTINATION include/engine
        FILES_MATCHING PATTERN "*.hpp")

install(TARGETS ${PROJECT_NAME}
        DESTINATION lib/)
