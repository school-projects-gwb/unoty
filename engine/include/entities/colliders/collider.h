#ifndef ENGINE_INCLUDE_ENTITIES_COLLIDERS_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_COLLIDERS_COLLIDER_H_

#include "entities/component.h"

namespace engine::entities {

enum class ColliderType {
  Box, Circle
};

/// @brief Base for colliders
class Collider : public Component {
 public:
  virtual ~Collider() = default;

  // @brief Used internally for type checking purposes
  [[nodiscard]] virtual ColliderType GetType() const = 0;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COLLIDERS_COLLIDER_H_
