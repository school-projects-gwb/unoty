cmake_minimum_required(VERSION 3.26)
project(engine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cc src/*.h src/*/*.cc src/*/*.h src/*/*/*.h)

add_library(engine ${SOURCES}
        include/engine/engine_config.h
        include/entities/animator.h
        include/entities/sprite.h
        include/entities/rigid_body.h
        include/entities/colliders/polygon_collider.h
        include/entities/audio_source.h
        include/entities/ui/ui_object.h
        include/entities/ui/text.h
        include/entities/ui/button.h
        include/entities/camera.h
        include/entities/listeners/mouse_listener.h
        include/entities/listeners/key_listener.h)

target_include_directories(engine PUBLIC include/)