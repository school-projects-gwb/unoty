#ifndef ENGINE_INCLUDE_ENGINE_ENGINE_H_
#define ENGINE_INCLUDE_ENGINE_ENGINE_H_

#include "entities/scene/scene_callback_function.h"
#include "engine_config.h"

namespace engine {

/// @brief Starting point of a game; provides ability to start game and manage scenes.
class Engine {
 public:
  ~Engine();
  explicit Engine(engine::EngineConfig);
  void Start();
  void AddScene(const std::string& scene_name, entities::SceneCallbackFunction callback_function);
  void SetActiveScene(const std::string& scene_name);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENGINE_ENGINE_H_
