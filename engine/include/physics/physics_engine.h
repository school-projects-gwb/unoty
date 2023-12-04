#ifndef ENGINE_SRC_PHYSICS_PHYSICS_H_
#define ENGINE_SRC_PHYSICS_PHYSICS_H_

#include "entities/rigid_body.h"
#include "entities/colliders/collider.h"

namespace engine::physics {

	/// @brief Public interface for communicating with the physics library
	class PhysicsEngine {
	public:
      virtual ~PhysicsEngine() = default;
      virtual void Initialize(const entities::Vector2d& gravity) = 0;
      virtual void ExecutePhysicsStep(float step_time = 1.0f / 60.0f, int velocity_iterations = 6, int position_iterations = 2) = 0;
      virtual void DeregisterAllBodies() = 0;

      virtual void RegisterRigidBody(entities::GameObject& game_object, entities::RigidBody& rigid_body) = 0;
      virtual void SetRigidBodyAndTransformPosition(entities::GameObject& game_object, const entities::Vector2d& position) = 0;
      virtual void DeregisterRigidBody(entities::GameObject& game_object) = 0;
      virtual void ApplyForceTowardsDirection(entities::GameObject& game_object, entities::Vector2d direction) = 0;
      virtual void ApplyImpulseTowardsDirection(entities::GameObject& game_object, entities::Vector2d direction) = 0;

      virtual void RegisterCollider(entities::GameObject& game_object, const entities::Collider& collider) = 0;
    };
}

#endif //ENGINE_SRC_PHYSICS_PHYSICS_H_
