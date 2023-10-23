#ifndef ENGINE_INCLUDE_API_SCENE_H_
#define ENGINE_INCLUDE_API_SCENE_H_

#include "game_object.h"
namespace engine::entities {

/// @brief Contains all game objects and ability to update/render them
class Scene {
 public:
  ~Scene();
  Scene();
  void AddGameObject(std::shared_ptr<GameObject>object);
  void UpdateObjects();
  void RenderObjects();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_API_SCENE_H_
