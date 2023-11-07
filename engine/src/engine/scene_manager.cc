#include "scene_manager.h"
#include <utility>

namespace engine {

void SceneManager::AddScene(const std::string& scene_name, engine::entities::SceneCallbackFunction callback_function) {
  scenes_[scene_name] = std::move(callback_function);
}

void SceneManager::SetActiveScene(const std::string& scene_name) {
  if (scenes_.find(scene_name) == scenes_.end()) return;
  auto scene = std::shared_ptr<entities::Scene>( scenes_[scene_name]());
  active_scene_ = scene;
  active_scene_->InitialiseObjects();
}

std::shared_ptr<entities::Scene> SceneManager::GetActiveScene() {
  return active_scene_;
}

}
