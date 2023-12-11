#ifndef ENGINE_SRC_PHYSICS_BOX2D_PHYSICS_ENGINE_H
#define ENGINE_SRC_PHYSICS_BOX2D_PHYSICS_ENGINE_H

#include <memory>
#include <map>
#include <string>
#include "physics/physics_engine.h"
#include <box2d/box2d.h>
#include "entities/game_object.h"
#include "entities/colliders/box_collider.h"
#include "entities/colliders/circle_collider.h"
#include "box2d_contact_listener.h"

namespace engine::physics {

struct PhysicsConfig {
  int steps_per_second;
  int velocity_iterations;
  int position_iterations;
  entities::Vector2d gravity;
};

/// @brief Concrete physics engine implementation of Box2D
class Box2dPhysicsEngine : public PhysicsEngine {
 public:
  /// @brief Default constructor; initializes a world with {0f,0f} gravity
  Box2dPhysicsEngine(PhysicsConfig config);

  /// @brief Deletes the world and all objects in it
  ~Box2dPhysicsEngine();

  /// @brief Calculate the effects of physics on all registered components for one game step
  void ExecutePhysicsStep() override;

  /// @brief Sets the amount of gravity bodies experience
  /// @param gravity The amount of gravity experienced through one axis, axes can differ from eachother
  void SetGravity(const entities::Vector2d& gravity) override;

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

  /// @brief Directly set a bodies' velocity
  /// Can be called on the RigidBody component as well
  void SetLinearVelocity(entities::GameObject& game_object, entities::Vector2d direction) override;

  void DeregisterAllBodies() override;

  [[nodiscard]] std::vector<std::pair<entities::GameObject *, entities::GameObject *>> GetContactObjects(bool is_start_contacts) const override;

  void FinalizePhysicsStep() override;

  void SetStepsPerSecond(int steps_per_second) override;
 private:
  float step_time_;
  int velocity_iterations_;
  int position_iterations_;

  /// @brief Box2d works best when bodies are between 0.1 and 10 units in size.
  /// These variables can be used to convert sizes between the rendering library and the physics library.
  const float PHYSICS_SCALE_ = 0.01f;
  const float GRAPHICS_SCALE_ = PHYSICS_SCALE_ * 10000;

  /// @brief Converts the Unoty RigidBodyType to the Box2D equivalent
  static b2BodyType RigidBodyTypeToBox2D(physics::RigidBodyType rb_type);

  void RegisterBoxCollider(b2Body *body, const entities::BoxCollider &collider);
  void RegisterCircleCollider(b2Body *body, const entities::CircleCollider &collider);

  /// @brief The world performs physics calculations and holds and manages all entities that participate in physics
  b2World* world;
  Box2dContactListener* contact_listener_ = nullptr;

  /// @brief Maps pointers to b2Bodies to the name of the gameobject they are attached to
  /// Uses standard pointers to directly access a key-value pair
  std::map<entities::GameObject*, b2Body*> registered_bodies_;

  /// @brief Used for accessing GameObjects by b2Body as key
  ///
  /// Used in favor of box2d's UserData which uses void pointers and requires casting to object every time collision is handled
  std::map<b2Body*, entities::GameObject*> reversed_registered_bodies_;

  std::vector<std::pair<entities::Vector2d, entities::Vector2d>> collision_info_;

  entities::Vector2d GetGameObjectOffsetPosition(entities::GameObject *game_object);
};

} //namespace engine::physics

#endif //ENGINE_SRC_PHYSICS_BOX2D_PHYSICS_ENGINE_H
