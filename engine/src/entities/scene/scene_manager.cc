#include "scene_manager.h"
#include "utility/debug.h"
#include <utility>

namespace engine {

SceneManager& SceneManager::GetInstance() {
  static SceneManager instance;
  return instance;
}

void SceneManager::AddScene(const std::string& scene_name, engine::entities::SceneCallbackFunction callback_function) {
  if (scenes_.find(scene_name) == scenes_.end())
    scenes_[scene_name] = std::move(callback_function);
}

void SceneManager::RemoveScene(const std::string &scene_name) {
  scenes_.erase(scene_name);

  if (active_scene_ != nullptr && active_scene_->GetSceneName() == scene_name)
    active_scene_ = nullptr;
}

void SceneManager::SetActiveScene(const std::string& scene_name) {
  if (!TryFindAndSetNewActiveScene(scene_name)) {
    helpers::Debug::Log("Scene with name " + scene_name + " was not found!");
    return;
  }

  active_scene_->SetSceneName(scene_name);
  active_scene_->InitialiseObjects();
}

void SceneManager::SetActiveScene(const std::string &scene_name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate) {
  if (!TryFindAndSetNewActiveScene(scene_name)) return;

  for (auto& object : objects_to_migrate)
    active_scene_->AddObject(std::move(object)); // Move ownership of objects_to_migrate to new Scene

  active_scene_->InitialiseObjects();
}

bool SceneManager::TryFindAndSetNewActiveScene(const std::string &scene_name) {
  if (scenes_.find(scene_name) == scenes_.end()) return false;
  if (active_scene_ != nullptr) active_scene_->ClearAllObjects();
  auto scene = std::shared_ptr<entities::Scene>( scenes_[scene_name]());
  active_scene_ = scene;

  return true;
}

std::shared_ptr<entities::Scene> SceneManager::GetActiveScene() {
  return active_scene_;
}

std::vector<std::shared_ptr<entities::GameObject>> SceneManager::GetAllObjects() {
  if (active_scene_ == nullptr) return {};
  return active_scene_->GetAllObjects();
}

std::shared_ptr<entities::GameObject> SceneManager::GetObjectByName(const std::string &name, bool search_recursive) {
  if (active_scene_ == nullptr) return {};
  return active_scene_->GetObjectByName(name, search_recursive);
}

std::vector<std::shared_ptr<entities::GameObject>> SceneManager::GetObjectsByTagName(const std::string &tag_name, bool search_recursive) {
  if (active_scene_ == nullptr) return {};
  return active_scene_->GetObjectsByTagName(tag_name, search_recursive);
}

void SceneManager::AddObject(std::shared_ptr<entities::GameObject> object_to_add) {
  if (active_scene_ == nullptr) return;
  active_scene_->AddObject(object_to_add);
}

void SceneManager::RemoveObject(std::shared_ptr<entities::GameObject> object_to_remove) {
  if (active_scene_ == nullptr) return;
  active_scene_->RemoveObject(object_to_remove);
}

}
