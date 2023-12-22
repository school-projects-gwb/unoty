#ifndef ENGINE_INCLUDE_API_SCENE_H_
#define ENGINE_INCLUDE_API_SCENE_H_

#include <set>
#include "entities/game_object.h"
#include "rendering/renderer.h"
#include "entities/camera.h"
#include "entities/structs/key.h"
#include "physics/physics_engine.h"
#include "scene_background.h"
#include "entities/audio_source.h"
#include "entities/listeners/listener.h"
#include "entities/structs/input.h"
#include "entities/structs/debug_info.h"
#include "scene_lighting.h"

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
  void QueueObject(std::shared_ptr<GameObject> object);
  void RemoveObject(std::shared_ptr<GameObject> object_to_remove);

  void AddListener(std::shared_ptr<Listener> listener);

  /// @brief Handles initialisation logic such as triggering OnStart on BehaviourScript components
  void InitialiseObjects();

  /// @brief Triggers all Components in Scene's GameObjects that have input handling functionality
  void TriggerListeners();

  /// @brief Removes all Objects from Scene and adds them to the Scene's GameObjects
  void DequeueObjects();

  /// @brief Updates physics Components in Scene's GameObjects
  void UpdatePhysics(const std::unique_ptr<physics::PhysicsEngine> &physics);

  /// @brief Render all renderable Components in Scene's GameObjects
  void RenderObjects(const std::unique_ptr<ui::Renderer> &renderer);

  void RenderDebug(const std::unique_ptr<ui::Renderer> &renderer, const entities::DebugInfo &debug_info);

  void SetCamera(std::unique_ptr<Camera> camera);
  [[nodiscard]] const Point GetCameraPosition(bool with_offset) const;

  /// @brief Sets background containing TileMap and other background information
  void SetBackground(std::unique_ptr<SceneBackground> background);

  void SetLighting(std::unique_ptr<SceneLighting> lighting);
  [[nodiscard]] const std::unique_ptr<SceneLighting> &GetLighting() const;

  void SetBackgroundMusic(std::unique_ptr<AudioSource> music);

  void SetViewportRendering(bool viewport_rendering);
  void SetViewportRendering(bool viewport_rendering, float offset);

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string& tag_name, bool search_recursive = false);
  std::shared_ptr<GameObject> GetObjectByName(const std::string& name, bool search_recursive = false);
  std::vector<std::shared_ptr<GameObject>> GetAllObjects();

  /// @brief Clears all objects in current active Scene
  void ClearAllObjects();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_API_SCENE_H_
