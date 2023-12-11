#include <iostream>
#include "entities/game_object.h"
#include "entities/component.h"
#include "entities/scene/scene_manager.h"
#include "utility/debug.h"

namespace engine::entities {

class GameObject::Impl : public std::enable_shared_from_this<GameObject> {
 public:
  explicit Impl(GameObject* owner) : owner_(owner), transform_() {
    transform_ = std::make_shared<Transform>();
  }

  void SetName(const std::string &name) {
    auto name_check = GetSceneObjectByName(name);
    if (name_check == nullptr) {
      name_ = name;
      return;
    }

    utility::Debug::Log("Name " + name + " already in use for another object. Object has not been renamed");
  }

  const std::string &GetName() const {
    return name_;
  }

  void SetTagName(const std::string &tag_name) {
    tag_name_ = tag_name;
  }

  const std::string &GetTagName() const {
    return tag_name_;
  }

  void SetLayer(int layer) {
    layer_ = layer;
  }

  [[nodiscard]] int GetLayer() const {
    return layer_;
  }

  void SetIsActive(bool is_active) {
    is_active_ = is_active;
  }

  [[nodiscard]] bool GetIsActive() const {
    return is_active_;
  }

  std::shared_ptr<Transform> GetTransform() {
    return transform_;
  }

  static std::vector<std::shared_ptr<GameObject>> GetAllSceneObjects() {
    return SceneManager::GetInstance().GetAllObjects();
  }

  static std::shared_ptr<GameObject> GetSceneObjectByName(const std::string &name, bool search_recursive = false) {
    return SceneManager::GetInstance().GetObjectByName(name, search_recursive);
  }

  static std::vector<std::shared_ptr<GameObject>> GetSceneObjectsByTagName(const std::string &tag_name, bool search_recursive = false) {
    return SceneManager::GetInstance().GetObjectsByTagName(tag_name, search_recursive);
  }

  static void AddSceneObject(std::shared_ptr<GameObject> object_to_add) {
    SceneManager::GetInstance().AddObject(object_to_add);
  }

  static void RemoveSceneObject(std::shared_ptr<GameObject> object_to_remove) {
    SceneManager::GetInstance().RemoveObject(object_to_remove);
  }
 private:
  std::string name_;
  std::string tag_name_;
  bool is_active_ = true;
  int layer_ = 0;
  std::shared_ptr<GameObject> parent_;
  GameObject* owner_;
  std::shared_ptr<Transform> transform_;
};

GameObject::GameObject() : impl_(std::make_unique<Impl>(this)) {}
GameObject::~GameObject() = default;

void GameObject::SetName(const std::string &name) {
  impl_->SetName(name);
}

const std::string &GameObject::GetName() const {
  return impl_->GetName();
}

void GameObject::SetTagName(const std::string &tag_name) {
  impl_->SetTagName(tag_name);
}

const std::string &GameObject::GetTagName() const {
  return impl_->GetTagName();
}

void GameObject::SetLayer(int layer) {
  impl_->SetLayer(layer);
}

int GameObject::GetLayer() const {
  return impl_->GetLayer();
}

void GameObject::SetIsActive(bool is_active) {
  impl_->SetIsActive(is_active);
}

bool GameObject::GetIsActive() const {
  return impl_->GetIsActive();
}

std::shared_ptr<Transform> GameObject::GetTransform() {
  return impl_->GetTransform();
}

std::shared_ptr<Transform> GameObject::GetTransform() const {
  return impl_->GetTransform();
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetAllSceneObjects() {
  return Impl::GetAllSceneObjects();
}

std::shared_ptr<GameObject> GameObject::GetSceneObjectByName(const std::string &name, bool search_recursive) {
  return Impl::GetSceneObjectByName(name, search_recursive);
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetSceneObjectsByTagName(const std::string &tag_name, bool search_recursive) {
  return Impl::GetSceneObjectsByTagName(tag_name, search_recursive);
}

void GameObject::RemoveSceneObject(std::shared_ptr<GameObject> object_to_remove) {
  Impl::RemoveSceneObject(object_to_remove);
}

void GameObject::AddSceneObject(std::shared_ptr<GameObject> object_to_add) {
  Impl::AddSceneObject(object_to_add);
}

}