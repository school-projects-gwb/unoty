#ifndef ENGINE_INCLUDE_ENTITIES_COMPONENT_H_
#define ENGINE_INCLUDE_ENTITIES_COMPONENT_H_

#include "transform.h"
#include <memory>

namespace engine::entities {

/// @brief Base for components
class GameObject;
class Component {
 public:
  virtual ~Component() = default;

  /// @brief Sets the GameObject this Component belongs to
  ///
  /// Automatically used internally when creating new Component
  void SetGameObject(std::shared_ptr<GameObject> game_object) {
    game_object_ = game_object;
  }

  /// @brief Returns the GameObject this Component belongs to
  std::shared_ptr<GameObject> GetGameObject() {
    return game_object_.lock();
  }

  template <typename T, typename... Args>
  static std::shared_ptr<T> Create(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

 private:
  std::weak_ptr<GameObject> game_object_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COMPONENT_H_
