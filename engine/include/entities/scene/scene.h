#ifndef ENGINE_INCLUDE_API_SCENE_H_
#define ENGINE_INCLUDE_API_SCENE_H_

#include <set>
#include "entities/game_object.h"
#include "rendering/renderer.h"
#include "entities/camera.h"
#include "entities/structs/key.h"
#include "engine/physics.h"
#include "scene_background.h"
#include "entities/audio_source.h"
#include "entities/listeners/listener.h"
#include "entities/structs/input.h"

namespace engine::entities {

/// @brief Contains all game objects and ability to update/render them
class Scene {
 public:
  ~Scene();
  Scene();

  /// @brief Used internally to set name if not not yet set
  void SetSceneName(const std::string& scene_name);
  const std::string& GetSceneName();

  void AddObject(std::shared_ptr<GameObject> object);
  void RemoveObject(std::shared_ptr<GameObject> object_to_remove);

  void AddListener(std::shared_ptr<Listener> listener);

  void StartRenderFrame(const std::unique_ptr<ui::Renderer>& renderer);
  void EndRenderFrame(const std::unique_ptr<ui::Renderer>& renderer);

  /// @brief Handles initialisation logic such as triggering OnStart on BehaviourScript components
  void InitialiseObjects();

  /// @brief Triggers all Components in Scene's GameObjects that have input handling functionality
  void TriggerListeners();

  /// @brief Updates physics Components in Scene's GameObjects
  void UpdatePhysics(const std::unique_ptr<physics::Physics>& physics);

  /// @brief Render all renderable Components in Scene's GameObjects
  void RenderObjects(const std::unique_ptr<ui::Renderer>& renderer);

  void RenderDebug(const std::unique_ptr<ui::Renderer>& renderer, const std::string& font_path, int most_recent_fps);

  void SetCamera(std::unique_ptr<Camera> camera);

  /// @brief Sets background containing TileMap and other background information
  void SetBackground(std::unique_ptr<SceneBackground> background);

  void SetBackgroundMusic(std::unique_ptr<AudioSource> music);

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string& tag_name, bool search_recursive = false);
  std::shared_ptr<GameObject> GetObjectByName(const std::string& name, bool search_recursive = false);
  std::vector<std::shared_ptr<GameObject>> GetAllObjects();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_API_SCENE_H_
