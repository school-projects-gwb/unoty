#include "entities/colliders/collider.h"
#include "entities/colliders/circle_collider.h"

namespace engine::entities {

class CircleCollider::Impl : public Collider {
 public:
  Impl() {

  }
};

CircleCollider::~CircleCollider() = default;
CircleCollider::CircleCollider() : impl_(new Impl()) {
}

}