#ifndef ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_
#define ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_

#include <vector>
#include <memory>
#include <algorithm>
#include "component.h"

namespace engine::entities {

/// @brief Base for GameObjects, contains various helper methods for handling game objects
class GameObject : public std::enable_shared_from_this<GameObject> {
 public:
  GameObject();
  ~GameObject();

  std::shared_ptr<Transform> GetTransform();

  void SetParent(std::shared_ptr<GameObject> parent);
  std::shared_ptr<GameObject> GetParent() const;

  /// @brief Sets name, unique identifier (can only appear once; or else it will not be set)
  void SetName(const std::string& name);
  const std::string& GetName() const;

  void SetTagName(const std::string& tag_name);
  const std::string& GetTagName() const;

  void SetLayer(int layer);
  int GetLayer() const;

  void SetIsActive(bool is_active);
  bool GetIsActive() const;

  template<class T>
  void AddComponent(std::shared_ptr<T> component);

  template<class T>
  std::shared_ptr<T> GetComponentByType();

  /// @brief Returns every single object from the current active Scene
  static std::vector<std::shared_ptr<GameObject>> GetAllObjects();

  /// @brief Get a vector (can be empty) of all objects in current active Scene that have the given tag name
  static std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string& tag_name);

  /// @brief Get singular object (can be nullptr) in current active Scene by name which acts as a unique identifier
  static std::shared_ptr<GameObject> GetObjectByName(const std::string& name);

  static void AddObject(std::shared_ptr<GameObject> object_to_add);

  /// @brief If given object shared pointer exists in Scene it will be removed
  static void RemoveObject(std::shared_ptr<GameObject> object_to_remove);

  template<class T>
  std::vector<std::shared_ptr<T>> GetComponentsByType();

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
  component->SetGameObject(shared_from_this());
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

template<class T>
std::vector<std::shared_ptr<T>> GameObject::GetComponentsByType() {
  std::vector<std::shared_ptr<T>> matching_components;

  for (const auto& component : components_) {
    auto typedComponent = std::dynamic_pointer_cast<T>(component);
    if (typedComponent) matching_components.push_back(typedComponent);
  }

  return matching_components;
}

}


#endif //ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_
