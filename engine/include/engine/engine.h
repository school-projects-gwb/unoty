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
  void Init();

  /// @brief Starts engine loop based on EngineConfig and current active Scene
  void Start();

  /// @brief "Pauses" the game loop; it will only run the unpause_handling_callback.
  ///
  /// Inside the unpause_handling_callback logic can be added to conditionally unpause the game again.
  void Pause(std::function<void()> unpause_handling_callback);

  /// @brief Stops engine loop after current game tick, shuts down engine and application
  void Stop();

  void AddScene(const std::string& scene_name, entities::SceneCallbackFunction callback_function);

  /// @brief Sets (overrides) active Scene if found based on scene_name
  ///
  /// Note that any GameObjects in this Scene will be discarded if they are not tracked anywhere else
  void SetActiveScene(const std::string& scene_name);

  void ToggleDebugMode() const;
  [[nodiscard]] bool IsDebugModeEnabled() const;

  /// @brief Shuts down engine
  ///
  /// @warning DO NOT use from within game script code; use Stop() instead. This function effectively destroys Engine pointer.
  /// Also ensure this function gets called AFTER Start() to prevent memory leaks and ensure correct shutdown.
  void Shutdown();

  /// @overload With GameObjects that will be transferred to the new Scene
  void SetActiveScene(const std::string& scene_name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate);

  /// @brief Used to dynamically update target frames per second between Scenes for example
  void SetFps(int frames_per_second);

  std::unique_ptr<physics::PhysicsEngine>& GetPhysicsEngine();
 private:
  class Impl;
  std::unique_ptr<Impl> impl_;

  Engine();
};

}

#endif //ENGINE_INCLUDE_ENGINE_ENGINE_H_
