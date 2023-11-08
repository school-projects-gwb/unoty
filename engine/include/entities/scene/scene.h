#ifndef ENGINE_INCLUDE_API_SCENE_H_
#define ENGINE_INCLUDE_API_SCENE_H_

#include <set>
#include "entities/game_object.h"
#include "engine/renderer.h"
#include "entities/camera.h"
#include "entities/structs/key.h"
#include "engine/physics.h"
#include "scene_background.h"
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

  /// @brief Handles initialisation logic such as triggering OnStart on BehaviourScript components
  void InitialiseObjects();

  /// @brief Triggers all Components in Scene's GameObjects that have input handling functionality
  void TriggerListeners(const std::set<entities::Key>& keys);

  /// @brief Updates physics Components in Scene's GameObjects
  void UpdatePhysics(const std::unique_ptr<physics::Physics>& physics);

  /// @brief Render all renderable Components in Scene's GameObjects
  void RenderObjects(const std::unique_ptr<ui::Renderer>& renderer);

  void SetCamera(std::unique_ptr<Camera> camera);

  /// @brief Sets background containing TileMap and other background information
  void SetBackground(std::unique_ptr<SceneBackground> background);

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string& tag_name);
  std::shared_ptr<GameObject> GetObjectByName(const std::string& name);
  std::vector<std::shared_ptr<GameObject>> GetAllObjects();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_API_SCENE_H_
