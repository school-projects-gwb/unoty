#ifndef ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_
#define ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_

#include <vector>
#include <memory>
#include <algorithm>
#include "component.h"

namespace engine::entities {

class SceneLighting;

/// @brief Base for GameObjects, contains various helper methods for handling game objects
class GameObject : public std::enable_shared_from_this<GameObject> {
 public:
  GameObject();
  virtual ~GameObject();

  std::shared_ptr<Transform> GetTransform();
  std::shared_ptr<Transform> GetTransform() const;

  void SetParent(GameObject *parent) {
    parent_object_ = parent;
  }

  GameObject *GetParent() {
    return parent_object_;
  }

  /// @brief Sets name, unique identifier (can only appear once; or else it will not be set)
  void SetName(const std::string &name);
  const std::string &GetName() const;

  void SetTagName(const std::string &tag_name);
  const std::string &GetTagName() const;

  void SetLayer(int layer);
  int GetLayer() const;

  void SetIsActive(bool is_active);
  bool GetIsActive() const;

  /// @brief Returns every single object from the current active Scene
  static std::vector<std::shared_ptr<GameObject>> GetAllSceneObjects();

  /// @brief Get a vector (can be empty) of all objects in current active Scene that have the given tag name
  ///
  /// \param search_recursive Whether to search recursively through child GameObjects
  static std::vector<std::shared_ptr<GameObject>> GetSceneObjectsByTagName(const std::string &tag_name,
                                                                           bool search_recursive = false);

  /// @brief Get singular object (can be nullptr) in current active Scene by name which acts as a unique identifier
  ///
  /// @param search_recursive Whether to search recursively through child GameObjects
  static std::shared_ptr<GameObject> GetSceneObjectByName(const std::string &name, bool search_recursive = false);

  /// @brief Returns the SceneLighting object for easy access and modification from within Scene objects/components during runtime
  static const std::unique_ptr<SceneLighting> &GetSceneLightingObject();

  /// @brief Used when adding new GameObject to Scene from i.e. a BehaviourScript script
  ///
  /// @note When in a Scene initialisation script, it makes more sense to call the AddObject on the Scene directly.
  static void AddSceneObject(std::shared_ptr<GameObject> object_to_add);

  /// @brief If given object shared pointer exists in Scene it will be removed
  static void RemoveSceneObject(std::shared_ptr<GameObject> object_to_remove);

  template<typename... Args>
  static std::shared_ptr<GameObject> Create(Args &&... args) {
    return std::make_shared<GameObject>(std::forward<Args>(args)...);
  }

  template<typename T, typename... Args>
  static std::shared_ptr<T> Create(Args &&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

  template<class T>
  void AddComponent(std::shared_ptr<T> component);

  template<class T>
  std::shared_ptr<T> GetComponentByType();

  template<class T>
  std::vector<std::shared_ptr<T>> GetComponentsByType();

  template<class T>
  void AddChildObject(std::shared_ptr<T> child_object);

  template<class T>
  void RemoveChildObject(std::shared_ptr<T> child_object);

  std::vector<std::shared_ptr<GameObject>> GetChildObjects() {
    return child_objects_;
  }

  /// @brief Used to cast GameObject to different implementation type
  template<class T>
  static std::shared_ptr<T> Cast(std::shared_ptr<GameObject> target_object) {
    return std::dynamic_pointer_cast<T>(target_object);
  }

  /// @brief Used to cast raw pointer GameObject to different implementation type
  template<class T>
  static T *Cast(GameObject *target_object) {
    return dynamic_cast<T *>(target_object);
  }
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
  std::vector<std::shared_ptr<Component>> components_;
  std::vector<std::shared_ptr<GameObject>> child_objects_;
  GameObject *parent_object_ = nullptr;

  friend class Impl;
};

template<class T>
void GameObject::AddComponent(std::shared_ptr<T> component) {
  component->SetGameObject(*this);
  components_.emplace_back(component);
}

template<class T>
std::shared_ptr<T> GameObject::GetComponentByType() {
  auto found_component =
      std::find_if(components_.begin(), components_.end(), [](const std::shared_ptr<Component> &component) {
        return std::dynamic_pointer_cast<T>(component) != nullptr;
      });

  if (found_component != components_.end()) return std::dynamic_pointer_cast<T>(*found_component);

  return nullptr;
}

template<class T>
std::vector<std::shared_ptr<T>> GameObject::GetComponentsByType() {
  std::vector<std::shared_ptr<T>> matching_components;

  for (const auto &component : components_) {
    auto typedComponent = std::dynamic_pointer_cast<T>(component);
    if (typedComponent) matching_components.push_back(typedComponent);
  }

  return matching_components;
}

template<class T>
void GameObject::AddChildObject(std::shared_ptr<T> child_object) {
  if (child_object->GetParent() != nullptr) return;
  child_objects_.emplace_back(child_object);
  child_object->SetParent(this);
}

template<class T>
void GameObject::RemoveChildObject(std::shared_ptr<T> child_object) {
  auto it = std::remove_if(child_objects_.begin(), child_objects_.end(),
                           [&child_object](const std::shared_ptr<T> &obj) {
                             return obj == child_object;
                           });

  // Erase removed element from child_objects vector
  child_objects_.erase(it, child_objects_.end());

  // Update the parent pointer of the child object to null
  if (child_object) {
    child_object->SetParent(nullptr);
  }
}

}

#endif //ENGINE_INCLUDE_ENTITIES_GAME_OBJECT_H_
