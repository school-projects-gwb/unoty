#include <memory>
#include <iostream>
#include "entities/colliders/box_collider.h"
#include <box2d/box2d.h>

namespace engine::entities {

class BoxCollider::Impl : public Collider {
 public:
  Impl() {
    //todo: finish adding params to constructor, check for existing transform for dimensions, check for existing rigidbody
//    b2PolygonShape shape_;
//    shape_.SetAsBox(half_width_size.x, half_width_size.y); // Set the dimensions of the box (half-width, half-height)
//
//    // Define the dynamic body fixture.
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &shape_;
//
//    // Set the box density to be non-zero, so it will be dynamic.
//    fixtureDef.density = 1.0f;
//
//    // Override the default friction.
//    fixtureDef.friction = 0.3f;
//
//    // Add the shape to the body.
//    wrapped_body->CreateFixture(&fixtureDef);
  }
};

BoxCollider::~BoxCollider() = default;
BoxCollider::BoxCollider() : impl_(new Impl()) {
}

}