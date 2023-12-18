#ifndef ENGINE_INCLUDE_ENTITIES_PHYSICS_RIGID_BODY_H_
#define ENGINE_INCLUDE_ENTITIES_PHYSICS_RIGID_BODY_H_

#include "entities/component.h"
#include "entities/structs/rigid_body_type.h"
#include "entities/structs/vector_2d.h"
#include "entities/physics/collider.h"
#include <memory>

namespace engine::entities {

/// @brief Component used to allow the parent gameobject to partake in physics simulation
class RigidBody : public Component {
 public:
  explicit RigidBody(GameObject &parent, physics::RigidBodyType rb_type);
  explicit RigidBody(GameObject &parent, physics::RigidBodyType rb_type, const std::shared_ptr<Collider>& collider);
  ~RigidBody();

  /// @brief Sets the position of both the rigidbody and the transform
  /// Can be called on the PhysicsEngine as well
  void SetPosition(const Vector2d &position);

  /// @brief Moves the rigidbody towards a direction, takes time to accelerate, a larger force will accelerate the body faster
  /// Can be called on the PhysicsEngine as well
  /// @param direction Defines both the direction and magnitude of the force
  void ApplyForceTowardsDirection(entities::Vector2d direction);

  /// @brief Moves the rigidbody towards a direction, with instantaneous acceleration
  /// Can be called on the PhysicsEngine as well
  void ApplyImpulseTowardsDirection(entities::Vector2d direction);

  void SetLinearVelocity(entities::Vector2d velocity);

  void SetCollider(const std::shared_ptr<Collider>& collider);

  /// @brief Registers the RigidBody to the physics engine
  ///
  /// @note Only call this after initialising all required logic/data (colliders and/or GameObject's Transform Size)
  void Register();

  physics::RigidBodyType GetRigidBodyType();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_PHYSICS_RIGID_BODY_H_
