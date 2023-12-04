#ifndef ENGINE_INCLUDE_ENGINE_CONFIG_H_
#define ENGINE_INCLUDE_ENGINE_CONFIG_H_

#include "string"

namespace engine {

/// @brief Configurable starting options for the Engine
struct EngineConfig {
  static int game_tick_fps;
  static bool is_debug_mode;
  static bool is_paused;
  static std::string debug_font_path;

  // Rendering
  static int window_width;
  static int window_height;
  static std::string window_title;
  static bool no_sound_mode;
};

}

#endif //ENGINE_INCLUDE_ENGINE_CONFIG_H_
