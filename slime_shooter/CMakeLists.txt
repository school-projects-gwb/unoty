cmake_minimum_required(VERSION 3.22)
project(slime_shooter)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wpedantic)
add_compile_options("$<$<CONFIG:DEBUG>:-g>")

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32
            src/main.cc)

    set(CMAKE_EXE_LINKER_FLAGS
            "-static-libgcc -static-libstdc++ -static -Wl,-allow-multiple-definition")

else ()
    add_executable(${PROJECT_NAME}
            src/main.cc
            src/scenes/showcase/light_scene.h
            src/showcase/platformer/player.h
            src/showcase/platformer/player_movement.h)
endif ()

target_sources(${PROJECT_NAME} PRIVATE
        src/scenes/game_scene.h
        src/player/player_movement.h
        src/scenes/menu_scene.h
        src/debug_toggle_script.h
        src/player/player.h
        src/ui/hud/health_bar/health_bar.h
        src/ui/hud/experience_bar/experience_bar.h
        src/ui/hud/hud.h
        src/ui/hud/experience_bar/experience_bar_logo.h
        src/ui/hud/experience_bar/experience_bar_fill.h
        src/ui/hud/experience_bar/experience_bar_text.h
        src/ui/hud/health_bar/health_bar_fill.h
        src/ui/hud/health_bar/health_bar_logo.h
        src/ui/hud/health_bar/health_bar_text.h
        src/ui/hud/score/score_text.h
        src/common/definitions.h
        src/ui/menu/buttons/play_game_button.h
        src/ui/button_click_listener.h
        src/ui/menu/buttons/edit_level_button.h
        src/ui/menu/buttons/create_level_button.h
        src/ui/menu/highscore.h
        src/statistics/statistics.h
        src/statistics/statistic.h
        src/statistics/statistic_type.h
        src/statistics/upgrades/statistic_upgrade.h
        src/ui/hud/health_bar/health_bar_logic.h
        src/ui/hud/experience_bar/experience_bar_logic.h
        src/ui/hud/score/score_logic.h
        src/player_base/fireplace_object.h
        src/player_base/base_object.h
        src/player_base/bed_object.h
        src/enemies/enemy_logic.h
        src/enemies/enemy_attack.h
        src/enemies/enemy_object_pool.h
        src/enemies/enemy_spawner.h
        src/enemies/enemy_spawner_logic.h
        src/enemies/enemy_variants/enemy_base.h
        src/enemies/enemy_variants/pink_slime_enemy.h
        src/enemies/enemy_variants/orange_slime_enemy.h
        src/enemies/enemy_variants/ghost_enemy.h
        src/player/player_weapon.h
        src/player/player_weapon_logic.h
        src/player/player_turret.h
        src/scenes/level_editor_scene.h
        src/ui/level_editor/buttons/save_level_button.h
        src/ui/level_editor/buttons/back_button.h
        src/ui/level_editor/tilemap_selector/tilemap_selector.h
        src/ui/level_editor/tilemap_selector/tilemap_next_button.h
        src/ui/level_editor/tilemap_selector/tilemap_previous_button.h
        src/ui/level_editor/audio_selector/audio_next_button.h
        src/ui/level_editor/audio_selector/audio_previous_button.h
        src/ui/level_editor/audio_selector/audio_selector.h
        src/config/level_loader_config.h
        src/config/game_config.h
        src/ui/menu/level_selector/level_selector.h
        src/ui/menu/level_selector/level_next_button.h
        src/ui/menu/level_selector/level_previous_button.h
        src/ui/menu/buttons/quit_game_button.h
        src/config/level_editor_config.h
        src/ui/menu/buttons/delete_level_button.h
        src/upgrades/base_upgrade.h
        src/upgrades/base_upgrade_symbol.h
        src/ui/level_editor/editor_objects/draggable_object.h
        src/ui/level_editor/editor_objects/drag_handler.h
        src/config/source_files/level_editor_config.cc
        src/config/source_files/level_loader_config.cc
        src/config/source_files/game_config.cc
        src/player_base/base_logic.h
        src/ui/popup/popup.h
        src/ui/popup/popup_title.h
        src/ui/popup/popup_content.h
        src/upgrades/base_upgrade_logic.h
        src/player_base/particle/smoke_emitter.h
        src/player/player_experience.h
        src/upgrades/upgrade_handler/upgrade_handler.h
        src/upgrades/upgrade_handler/upgrade_option.h
        src/experience/experience_object_pool.h
        src/experience/experience.h
        src/experience/experience_logic.h
        src/ui/game_over/game_over_popup.h
        src/player/player_health.h
        src/projectiles/enemy_projectile_object_pool.h
        src/projectiles/player_projectile_object_pool.h
        src/projectiles/projectile.h
        src/projectiles/projectile_logic.h
        src/config/projectile_config.h
        src/player/player_light.h
        src/player/player_light_logic.h
        src/player_base/fireplace_light.h
)

target_include_directories(slime_shooter PRIVATE src)

target_compile_features(slime_shooter PUBLIC cxx_std_17)
target_link_libraries(slime_shooter PRIVATE
        engine)

add_custom_target(game_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${INSTALL_DIR}/resources")
