#ifndef ENGINE_INCLUDE_ENTITIES_COLLIDERS_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_COLLIDERS_COLLIDER_H_

#include "entities/component.h"

namespace engine::entities {

/// @brief Base for colliders
class Collider : public Component {
 public:
  virtual ~Collider() = default;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COLLIDERS_COLLIDER_H_
