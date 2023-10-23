#ifndef ENGINE_INCLUDE_ENGINE_CONFIG_H_
#define ENGINE_INCLUDE_ENGINE_CONFIG_H_

namespace engine {

/// @brief Configurable starting options for the Engine
struct EngineConfig {
  int game_tick_fps = 60;
  int render_tick_fps = 30;
  bool is_debug_mode = true;
};

}

#endif //ENGINE_INCLUDE_ENGINE_CONFIG_H_
