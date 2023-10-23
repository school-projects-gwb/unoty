#ifndef ENGINE_INCLUDE_ENTITIES_COLLIDERS_CIRCLE_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_COLLIDERS_CIRCLE_COLLIDER_H_

#include <memory>
#include "collider.h"

namespace engine::entities {

/// @brief Collider - circular shape
class CircleCollider : public Collider {
 public:
  ~CircleCollider();
  CircleCollider();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COLLIDERS_CIRCLE_COLLIDER_H_
