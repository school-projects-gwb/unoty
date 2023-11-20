cmake_minimum_required(VERSION 3.22)
project(slime_shooter)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(-Wall -Wpedantic)
add_compile_options("$<$<CONFIG:DEBUG>:-g>")

add_executable(slime_shooter src/main.cc
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
        src/ui/menu/buttons/button_click_listener.h
        src/ui/menu/buttons/load_level_button.h
        src/ui/menu/buttons/level_editor_button.h
        src/ui/menu/highscore.h
        src/statistics/statistics.h
        src/statistics/statistic.h
        src/statistics/statistic_type.h
        src/statistics/upgrades/statistic_upgrade.h
        src/ui/hud/health_bar/health_bar_logic.h
        src/ui/hud/experience_bar/experience_bar_logic.h
        src/ui/hud/score/score_logic.h
        src/world/fireplace_object.h
        src/world/base_object.h
        src/world/bed_object.h
        src/enemies/enemy_logic.h
        src/enemies/enemy_attack.h
        src/enemies/enemy_object_pool.h
        src/enemies/enemy_spawner.h
        src/enemies/enemy_variants/pink_slime_enemy.h
        src/enemies/enemy_variants/orange_slime_enemy.h
        src/enemies/enemy_variants/ghost_enemy.h
        src/enemies/enemy_projectile_object_pool.h
        src/player/player_weapon.h
        src/player/player_weapon_logic.h
        src/player/player_turret.h
)

target_include_directories(slime_shooter PRIVATE src)

target_compile_features(slime_shooter PUBLIC cxx_std_17)
target_link_libraries(slime_shooter PRIVATE engine)

add_custom_target(game-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")
