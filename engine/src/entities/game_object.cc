#include <iostream>
#include "entities/game_object.h"
#include "entities/component.h"

namespace engine::entities {

class GameObject::Impl {
 public:
  Impl(GameObject* owner) : owner_(owner) {}
 private:
  const GameObject* owner_;
};

GameObject::GameObject() : impl_(std::make_unique<Impl>(this)) {}
GameObject::~GameObject() = default;

}