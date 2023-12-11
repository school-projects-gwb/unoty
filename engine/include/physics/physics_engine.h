#ifndef ENGINE_SRC_PHYSICS_PHYSICS_H_
#define ENGINE_SRC_PHYSICS_PHYSICS_H_

#include "entities/rigid_body.h"
#include "entities/colliders/collider.h"
#include <vector>

namespace engine::physics {

/// @brief Public interface for communicating with the physics library
class PhysicsEngine {
 public:
  virtual ~PhysicsEngine() = default;
  virtual void ExecutePhysicsStep() = 0;

  /// @brief Executes finalisation logic such as clearing collisions in this current step, used internally
  virtual void FinalizePhysicsStep() = 0;
  virtual void SetStepsPerSecond(int steps_per_second) = 0;
  virtual void SetGravity(const entities::Vector2d &gravity) = 0;

  virtual void RegisterRigidBody(entities::GameObject &game_object, entities::RigidBody &rigid_body) = 0;
  virtual void DeregisterRigidBody(entities::GameObject &game_object) = 0;
  virtual void DeregisterAllBodies() = 0;

  virtual void ApplyForceTowardsDirection(entities::GameObject &game_object, entities::Vector2d direction) = 0;
  virtual void ApplyImpulseTowardsDirection(entities::GameObject &game_object, entities::Vector2d direction) = 0;
  virtual void SetLinearVelocity(entities::GameObject &game_object, entities::Vector2d direction) = 0;

  virtual void SetRigidBodyAndTransformPosition(entities::GameObject &game_object,
                                                const entities::Vector2d &position) = 0;

  // @brief Registers collider, a valid RigidBody must exist for given game_object in order for this to work.
  virtual void RegisterCollider(entities::GameObject &game_object, const entities::Collider &collider) = 0;

  [[nodiscard]] virtual std::vector<std::pair<entities::GameObject *,
                                              entities::GameObject *>> GetContactObjects(bool begin_contacts) const = 0;

};
}

#endif //ENGINE_SRC_PHYSICS_PHYSICS_H_
