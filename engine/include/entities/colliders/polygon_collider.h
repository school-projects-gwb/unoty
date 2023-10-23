#ifndef ENGINE_INCLUDE_ENTITIES_COLLIDERS_POLYGON_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_COLLIDERS_POLYGON_COLLIDER_H_

#include "collider.h"
namespace engine::entities {

/// @brief Collider - polygon shape
class PolygonCollider : public Collider {
 public:
  ~PolygonCollider();
  PolygonCollider();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COLLIDERS_POLYGON_COLLIDER_H_
