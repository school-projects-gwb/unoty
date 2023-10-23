#ifndef ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_
#define ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_

#include <vector>
#include "component.h"

namespace engine::entities {

/// @brief Base for GameObjects, contains various helper methods for handling game objects
class GameObject {
 public:
  GameObject();
  ~GameObject();

  template<class T>
  void AddComponent(std::shared_ptr<T> component);

  template<class T>
  std::shared_ptr<T> GetComponentByType();

  template <typename... Args>
  static std::shared_ptr<GameObject> Create(Args&&... args) {
    return std::make_shared<GameObject>(std::forward<Args>(args)...);
  }
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
  std::vector<std::shared_ptr<Component>> components_;

  friend class Impl;
};

template<class T>
void GameObject::AddComponent(std::shared_ptr<T> component) {
  components_.emplace_back(component);
}

template<class T>
std::shared_ptr<T> GameObject::GetComponentByType() {
  auto found_component = std::find_if(components_.begin(), components_.end(), [](const std::shared_ptr<Component>& component) {
    return std::dynamic_pointer_cast<T>(component) != nullptr;
  });

  if (found_component != components_.end()) return std::dynamic_pointer_cast<T>(*found_component);

  return nullptr;
}

}


#endif //ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_
