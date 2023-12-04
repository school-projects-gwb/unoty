#ifndef ENGINE_INCLUDE_ENTITIES_FIXTURE_H_
#define ENGINE_INCLUDE_ENTITIES_FIXTURE_H_

#include "entities/component.h"
#include "rigid_body.h"
#include "entities/structs/rigid_body_type.h"
#include "entities/structs/vector_2d.h"

namespace engine::entities {

/// @brief Used for affixing shapes to a rigid body for collision detection
class Fixture : public Component {
 public:
  Fixture() = default;
  //todo: implement
//  Fixture(physics::RigidBodyType rb_type, const physics::Vector2D &position, const physics::Vector2D &half_width_size)
//      : rb_type(rb_type), position(position), half_width_size(half_width_size) {}
//  ~Fixture();
//  physics::RigidBodyType rb_type = physics::RigidBodyType::RBNone;
//  physics::Vector2D position;
//  physics::Vector2D half_width_size;
//
//  /// Get the parent body of this fixture. This is nullptr if the fixture is not attached.
//  /// @return the parent body.
//  RigidBody* GetBody();
//  const RigidBody* GetBody() const;
//
// private:
//  class Impl;
//  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_FIXTURE_H_
