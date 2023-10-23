#ifndef ENGINE_INCLUDE_ENTITIES_COMPONENT_H_
#define ENGINE_INCLUDE_ENTITIES_COMPONENT_H_

#include "transform.h"
#include <memory>

namespace engine::entities {

/// @brief Base for components
class Component {
 public:
  virtual ~Component() = default;

  template <typename T, typename... Args>
  static std::shared_ptr<T> Create(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COMPONENT_H_
