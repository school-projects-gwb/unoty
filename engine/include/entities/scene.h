#ifndef ENGINE_INCLUDE_API_SCENE_H_
#define ENGINE_INCLUDE_API_SCENE_H_

#include "game_object.h"
#include "engine/renderer.h"
#include "camera.h"
#include "entities/structs/key.h"
#include "engine/physics.h"
namespace engine::entities {

/// @brief Contains all game objects and ability to update/render them
class Scene {
 public:
  ~Scene();
  Scene();
  void AddObject(std::shared_ptr<GameObject> object);
  void TriggerInputs(const entities::Key& key);
  void UpdatePhysics(const std::unique_ptr<physics::Physics>& physics);
  void RenderObjects(const std::unique_ptr<ui::Renderer>& renderer);
  void SetCamera(std::unique_ptr<Camera> camera);

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string& tag_name);
  std::shared_ptr<GameObject> GetObjectByName(const std::string& name);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_API_SCENE_H_
