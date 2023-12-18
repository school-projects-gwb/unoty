#include "entities/physics/collider.h"
#include "entities/physics/circle_collider.h"

namespace engine::entities {

class CircleCollider::Impl : public Collider {
 public:
  Impl(float radius) {
    radius_ = radius;
  }

  void SetRadius(float radius) {
    radius_ = radius;
  }

  [[nodiscard]] float GetRadius() const {
    return radius_;
  }

  [[nodiscard]] ColliderType GetType() const {
    return ColliderType::Circle;
  }

  float GetFriction() const {
    return friction_;
  }

  void SetFriction(float amount) {
    friction_ = amount;
  }

  float GetDensity() const {
    return density_;
  }

  void SetDensity(float amount) {
    density_ = amount;
  }

  void SetIsSensor(bool value) {
    is_sensor_ = value;
  }

  [[nodiscard]] bool GetIsSensor() const {
    return is_sensor_;
  }

 private:
  float radius_;
  float friction_ = 0.3f;
  float density_ = 1.0f;
  bool is_sensor_ = false;
};

CircleCollider::~CircleCollider() = default;
CircleCollider::CircleCollider(float radius) : impl_(new Impl(radius)) {
}

float CircleCollider::GetRadius() const {
  return impl_->GetRadius();
}

void CircleCollider::SetRadius(float radius) {
  impl_->SetRadius(radius);
}

ColliderType CircleCollider::GetType() const {
  return impl_->GetType();
}

float CircleCollider::GetFriction() const {
  return impl_->GetFriction();
}

void CircleCollider::SetFriction(float amount) {
  impl_->SetFriction(amount);
}

float CircleCollider::GetDensity() const {
  return impl_->GetDensity();
}

void CircleCollider::SetDensity(float amount) {
  impl_->SetDensity(amount);
}

bool CircleCollider::GetIsSensor() const {
  return impl_->GetIsSensor();
}

void CircleCollider::SetIsSensor(bool value) {
  impl_->SetIsSensor(value);
}

}