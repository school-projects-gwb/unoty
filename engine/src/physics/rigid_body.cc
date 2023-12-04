#include "entities/rigid_body.h"
#include "engine/engine.h"

namespace engine::entities {

RigidBody::RigidBody(GameObject& parent, physics::RigidBodyType rb_type)
  : rb_type(rb_type) {
  engine::Engine::GetInstance().GetPhysicsEngine()->RegisterRigidBody(parent, *this);
}

void RigidBody::SetPosition(const Vector2d& position) {
  engine::Engine::GetInstance().GetPhysicsEngine()->SetRigidBodyAndTransformPosition(GetGameObject(), position);
}

void RigidBody::ApplyForceTowardsDirection(entities::Vector2d direction) {
  engine::Engine::GetInstance().GetPhysicsEngine()->ApplyForceTowardsDirection(GetGameObject(), direction);
}

void RigidBody::ApplyImpulseTowardsDirection(entities::Vector2d direction) {
  engine::Engine::GetInstance().GetPhysicsEngine()->ApplyImpulseTowardsDirection(GetGameObject(), direction);
}

} // namespace engine::entities
