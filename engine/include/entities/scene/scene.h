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

  void AddObject(std::shared_ptr<GameObject> object);

  /// @brief Triggers all Components in Scene's GameObjects that have input handling functionality
  void TriggerInputs(const std::set<entities::Key>& keys);

  /// @brief Updates physics Components in Scene's GameObjects
  void UpdatePhysics(const std::unique_ptr<physics::Physics>& physics);

  /// @brief Render all renderable Components in Scene's GameObjects
  void RenderObjects(const std::unique_ptr<ui::Renderer>& renderer);

  void SetCamera(std::unique_ptr<Camera> camera);

  /// @brief Sets background containing TileMap and other background information
  void SetBackground(std::unique_ptr<SceneBackground> background);

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string& tag_name);

  std::shared_ptr<GameObject> GetObjectByName(const std::string& name);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_API_SCENE_H_
