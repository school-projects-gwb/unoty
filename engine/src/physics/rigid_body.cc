#include "entities/rigid_body.h"
#include "engine/engine.h"

namespace engine::entities {

class RigidBody::Impl : public Component {
 public:
  explicit Impl(GameObject &parent, RigidBody *owner, physics::RigidBodyType rb_type) :
      owner_(owner), parent_(parent), rb_type(rb_type) {}

  explicit Impl(GameObject &parent,
                RigidBody *owner,
                physics::RigidBodyType rb_type,
                std::shared_ptr<Collider> collider) :
      owner_(owner), parent_(parent), rb_type(rb_type), collider_(collider) {}

  void SetPosition(const Vector2d &position) {
    engine::Engine::GetInstance().GetPhysicsEngine()->SetRigidBodyAndTransformPosition(parent_, position);
  }

  physics::RigidBodyType GetRigidBodyType() {
    return rb_type;
  }

  void ApplyForceTowardsDirection(entities::Vector2d direction) {
    engine::Engine::GetInstance().GetPhysicsEngine()->ApplyForceTowardsDirection(parent_, direction);
  }

  void ApplyImpulseTowardsDirection(entities::Vector2d direction) {
    engine::Engine::GetInstance().GetPhysicsEngine()->ApplyImpulseTowardsDirection(parent_, direction);
  }

  void SetLinearVelocity(entities::Vector2d velocity) {
    engine::Engine::GetInstance().GetPhysicsEngine()->SetLinearVelocity(parent_, velocity);
  }

  void SetCollider(const std::shared_ptr<Collider> &collider) {
    engine::Engine::GetInstance().GetPhysicsEngine()->RegisterCollider(parent_, *collider);
  }

  void Register() {
    engine::Engine::GetInstance().GetPhysicsEngine()->RegisterRigidBody(parent_, *owner_);
    if (collider_ != nullptr)
      engine::Engine::GetInstance().GetPhysicsEngine()->RegisterCollider(parent_, *collider_);
  }

 private:
  RigidBody *owner_;
  GameObject &parent_;
  physics::RigidBodyType rb_type = physics::RigidBodyType::None;
  std::shared_ptr<Collider> collider_ = nullptr;
};

RigidBody::RigidBody(GameObject &parent, physics::RigidBodyType rb_type)
    : impl_(std::make_unique<Impl>(parent, this, rb_type)) {
  engine::Engine::GetInstance().GetPhysicsEngine()->RegisterRigidBody(parent, *this);
}

RigidBody::RigidBody(GameObject &parent, physics::RigidBodyType rb_type, const std::shared_ptr<Collider> &collider)
    : impl_(std::make_unique<Impl>(parent, this, rb_type, collider)) {}

RigidBody::~RigidBody() = default;

void RigidBody::SetPosition(const Vector2d &position) {
  impl_->SetPosition(position);
}

void RigidBody::ApplyForceTowardsDirection(entities::Vector2d direction) {
  impl_->ApplyForceTowardsDirection(direction);
}

void RigidBody::ApplyImpulseTowardsDirection(entities::Vector2d direction) {
  impl_->ApplyImpulseTowardsDirection(direction);
}

void RigidBody::SetLinearVelocity(entities::Vector2d velocity) {
  impl_->SetLinearVelocity(velocity);
}

physics::RigidBodyType RigidBody::GetRigidBodyType() {
  return impl_->GetRigidBodyType();
}

void RigidBody::SetCollider(const std::shared_ptr<Collider> &collider) {
  impl_->SetCollider(collider);
}

void RigidBody::Register() {
  impl_->Register();
}

} // namespace engine::entities
