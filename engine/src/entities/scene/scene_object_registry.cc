#include "scene_object_registry.h"
#include <iostream>

namespace engine::entities {

std::vector<std::shared_ptr<GameObject>> SceneObjectRegistry::GetObjects() {
  return game_objects_;
}

void SceneObjectRegistry::AddObject(std::shared_ptr<GameObject> object) {
  auto it = std::find(game_objects_.begin(), game_objects_.end(), object);
  if (it != game_objects_.end()) return;

  // Object not found, insert it
  auto insert_position = std::lower_bound(game_objects_.begin(), game_objects_.end(), object,
                                          [](const std::shared_ptr<GameObject> &a,
                                             const std::shared_ptr<GameObject> &b) {
                                            return a->GetLayer() < b->GetLayer();
                                          });

  game_objects_.insert(insert_position, std::move(object));

}

void SceneObjectRegistry::RemoveObject(std::shared_ptr<GameObject> object) {
  game_objects_.erase(std::remove_if(game_objects_.begin(), game_objects_.end(),
                                     [&object](const std::shared_ptr<GameObject> &obj) {
                                       return obj == object;
                                     }), game_objects_.end());
}

std::vector<std::shared_ptr<GameObject>> SceneObjectRegistry::GetObjectsByTagName(const std::string &tag_name,
                                                                                  bool search_recursive) {
  std::vector<std::shared_ptr<GameObject>> compatible_objects;

  for (const auto &game_object : game_objects_) {
    if (!search_recursive) {
      if (game_object->GetTagName() == tag_name)
        compatible_objects.emplace_back(game_object);
    } else {
      RecursiveTagSearch(game_object, tag_name, compatible_objects);
    }
  }

  return compatible_objects;
}

std::shared_ptr<GameObject> SceneObjectRegistry::GetObjectByName(const std::string &name, bool search_recursive) {
  for (const auto &game_object : game_objects_) {
    if (!search_recursive) {
      if (game_object->GetName() == name)
        return game_object;
    } else {
      auto result = RecursiveNameSearch(game_object, name);
      if (result)
        return result;
    }
  }

  return nullptr;
}

void SceneObjectRegistry::AddListener(std::shared_ptr<Listener> listener) {
  if (auto key_listener = std::dynamic_pointer_cast<KeyListener>(listener)) {
    key_listeners_.push_back(key_listener);
  } else if (auto mouse_listener = std::dynamic_pointer_cast<MouseListener>(listener)) {
    mouse_listeners_.push_back(mouse_listener);
  }
}

void SceneObjectRegistry::RecursiveTagSearch(const std::shared_ptr<GameObject> &object,
                                             const std::string &tag_name,
                                             std::vector<std::shared_ptr<GameObject>> &compatible_objects) {
  if (object->GetTagName() == tag_name)
    compatible_objects.emplace_back(object);

  for (const auto &child_object : object->GetChildObjects())
    RecursiveTagSearch(child_object, tag_name, compatible_objects);
}

std::shared_ptr<GameObject> SceneObjectRegistry::RecursiveNameSearch(const std::shared_ptr<GameObject> &object,
                                                                     const std::string &name) {
  if (object->GetName() == name)
    return object;

  for (const auto &child_object : object->GetChildObjects()) {
    auto result = RecursiveNameSearch(child_object, name);
    if (result)
      return result;
  }

  return nullptr;
}

void SceneObjectRegistry::Reset() {
  key_listeners_.clear();
  mouse_listeners_.clear();
  game_objects_.clear();
}

}
