#include <memory>
#include <iostream>
#include "entities/colliders/box_collider.h"

namespace engine::entities {

class BoxCollider::Impl : public Collider {
 public:
  Impl() {

  }
};

BoxCollider::~BoxCollider() = default;
BoxCollider::BoxCollider() : impl_(new Impl()) {
}

}