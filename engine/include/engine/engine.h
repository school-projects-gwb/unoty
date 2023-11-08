#ifndef ENGINE_INCLUDE_ENGINE_ENGINE_H_
#define ENGINE_INCLUDE_ENGINE_ENGINE_H_

#include "entities/scene/scene_callback_function.h"
#include "engine_config.h"

namespace engine {

/// @brief Starting point of a game; provides ability to start game and manage scenes.
class Engine {
 public:
  ~Engine();

  /// @brief Singleton instance so that it can be used across the application to i.e. easily switch Scenes.
  static Engine& GetInstance();

  /// @brief Initialises configuration; will not be able to Start() engine before having done this.
  void InitWithConfig(engine::EngineConfig config);

  /// @brief Starts engine loop based on EngineConfig and current active Scene
  void Start();

  void AddScene(const std::string& scene_name, entities::SceneCallbackFunction callback_function);

  /// @brief Sets (overrides) active Scene if found based on scene_name
  ///
  /// Note that any GameObjects in this Scene will be discarded if they are not tracked anywhere else
  void SetActiveScene(const std::string& scene_name);

  /// @overload With GameObjects that will be transferred to the new Scene
  void SetActiveScene(const std::string& scene_name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;

  Engine();
};

}

#endif //ENGINE_INCLUDE_ENGINE_ENGINE_H_
