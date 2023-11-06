#include <iostream>
#include "entities/game_object.h"
#include "entities/component.h"

namespace engine::entities {

class GameObject::Impl : public std::enable_shared_from_this<GameObject> {
 public:
  explicit Impl(GameObject* owner) : owner_(owner), transform_() {
    transform_ = std::make_shared<Transform>();
  }

  void SetParent(std::shared_ptr<GameObject> parent) {
    parent_ = parent;
  }

  std::shared_ptr<GameObject> GetParent() const {
    return parent_;
  }

  void SetName(const std::string &name) {
    name_ = name;
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

 private:
  std::string name_;
  std::string tag_name_;
  bool is_active_ = true;
  int layer_ = 0;
  std::shared_ptr<GameObject> parent_;
  const GameObject* owner_;
  std::shared_ptr<Transform> transform_;
};

GameObject::GameObject() : impl_(std::make_unique<Impl>(this)) {}
GameObject::~GameObject() = default;

void GameObject::SetParent(std::shared_ptr<GameObject> parent) {
  impl_->SetParent(parent);
}

std::shared_ptr<GameObject> GameObject::GetParent() const {
  return impl_->GetParent();
}

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

}