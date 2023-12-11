#include "engine/engine_config.h"

namespace engine {

int engine::EngineConfig::game_tick_fps = 60;
bool engine::EngineConfig::is_debug_mode = true;
bool engine::EngineConfig::is_paused = false;
bool engine::EngineConfig::no_sound_mode = false;
std::string engine::EngineConfig::debug_font_path = "/resources/fonts/PressStart2P-Regular.ttf";
int engine::EngineConfig::window_width = 1280;
int engine::EngineConfig::window_height = 700;
std::string engine::EngineConfig::window_title = "Slime Shooter";
entities::Vector2d engine::EngineConfig::gravity = {1.0f, 1.0f};

}