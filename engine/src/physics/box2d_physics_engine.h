#ifndef ENGINE_SRC_PHYSICS_BOX2D_PHYSICS_ENGINE_H
#define ENGINE_SRC_PHYSICS_BOX2D_PHYSICS_ENGINE_H

#include <memory>
#include <map>
#include <string>
#include "physics/physics_engine.h"
#include <box2d/box2d.h>
#include "entities/game_object.h"

namespace engine::physics {

/// @brief Concrete physics engine implementation of Box2D
class Box2dPhysicsEngine : public PhysicsEngine {
 public:
  /// @brief Default constructor; initializes a world with {0f,0f} gravity
  Box2dPhysicsEngine();

  /// @brief Deletes the world and all objects in it
  ~Box2dPhysicsEngine();

  /// @brief Reinitialize the worlds gravity
  void Initialize(const entities::Vector2d& gravity) override;

  /// @brief Calculate the effects of physics on all registered components for one game step
  void ExecutePhysicsStep(float step_time, int velocity_iterations, int position_iterations) override;

  /// @brief Called by the RigidBody constructor to register a Unoty rigidbody in the Box2D world
  void RegisterRigidBody(entities::GameObject& game_object, entities::RigidBody& rigid_body) override;

  /// @brief Remove the rigidbody attached to a gameobject from the physics calculations
  void DeregisterRigidBody(entities::GameObject& game_object) override;

  /// @brief Allows a gameobject to participate in collisions
  void RegisterCollider(entities::GameObject& game_object, const entities::Collider& collider) override;

  /// @brief Sets the position of both the rigidbody and the transform
  /// Can be called on the RigidBody component as well
  void SetRigidBodyAndTransformPosition(entities::GameObject& game_object, const entities::Vector2d& position) override;

  /// @brief Moves the rigidbody towards a direction, takes time to accelerate, a larger force will accelerate the body faster
  /// Can be called on the RigidBody component as well
  void ApplyForceTowardsDirection(entities::GameObject& game_object, entities::Vector2d direction) override;

  /// @brief Moves the rigidbody towards a direction, with instantaneous acceleration
  /// Can be called on the RigidBody component as well
  void ApplyImpulseTowardsDirection(entities::GameObject& game_object, entities::Vector2d direction) override;

  void DeregisterAllBodies() override;

 private:
  /// @brief Converts the Unoty RigidBodyType to the Box2D equivalent
  static b2BodyType RigidBodyTypeToBox2D(physics::RigidBodyType rb_type);

  /// @brief The world performs physics calculations and holds and manages all entities that participate in physics
  b2World* world;

  /// @brief Maps pointers to b2Bodies to the name of the gameobject they are attached to
  /// Uses standard pointers to directly access a key-value pair
  std::map<entities::GameObject*, b2Body*> registered_bodies_;
};

} //namespace engine::physics

#endif //ENGINE_SRC_PHYSICS_BOX2D_PHYSICS_ENGINE_H
