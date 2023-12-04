#ifndef ENGINE_INCLUDE_ENTITIES_RIGID_BODY_H_
#define ENGINE_INCLUDE_ENTITIES_RIGID_BODY_H_

#include "entities/component.h"
#include "entities/structs/rigid_body_type.h"
#include "entities/structs/vector_2d.h"
#include <memory>

namespace engine::entities {

/// @brief Component used to allow the parent gameobject to partake in physics simulation
class RigidBody : public Component {
 public:
  RigidBody(GameObject& parent, physics::RigidBodyType rb_type);

  /// @brief Sets the position of both the rigidbody and the transform
  /// Can be called on the PhysicsEngine as well
  void SetPosition(const Vector2d& position);

  /// @brief Moves the rigidbody towards a direction, takes time to accelerate, a larger force will accelerate the body faster
  /// Can be called on the PhysicsEngine as well
  /// @param direction Defines both the direction and magnitude of the force
  void ApplyForceTowardsDirection(entities::Vector2d direction);

  /// @brief Moves the rigidbody towards a direction, with instantaneous acceleration
  /// Can be called on the PhysicsEngine as well
  void ApplyImpulseTowardsDirection(entities::Vector2d direction);

  physics::RigidBodyType rb_type = physics::RigidBodyType::RBNone;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_RIGID_BODY_H_
