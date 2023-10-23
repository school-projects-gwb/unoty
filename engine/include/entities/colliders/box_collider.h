#ifndef ENGINE_INCLUDE_ENTITIES_COLLIDERS_BOX_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_COLLIDERS_BOX_COLLIDER_H_

#include <memory>
#include "collider.h"

namespace engine::entities {

/// @brief Collider - box/square shape
class BoxCollider : public Collider {
 public:
  ~BoxCollider();
  BoxCollider();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COLLIDERS_BOX_COLLIDER_H_
