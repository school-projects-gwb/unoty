#include <memory>
#include "entities/physics/box_collider.h"

namespace engine::entities {

class BoxCollider::Impl : public Collider {
 public:
  explicit Impl(Vector2d size) : size_(size) {}

  [[nodiscard]] Vector2d GetSize() const {
    return size_;
  }

  void SetSize(Vector2d size) {
    size_ = size;
  }

  [[nodiscard]] ColliderType GetType() const override {
    return ColliderType::Box;
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
  Vector2d size_;
  float friction_ = 0.3f;
  float density_ = 1.0f;
  bool is_sensor_ = false;
};

BoxCollider::BoxCollider(Vector2d size) : impl_(new Impl(size)) {}
BoxCollider::~BoxCollider() = default;

void BoxCollider::SetSize(Vector2d size) {
  impl_->SetSize(size);
}

Vector2d BoxCollider::GetSize() const {
  return impl_->GetSize();
}

ColliderType BoxCollider::GetType() const {
  return impl_->GetType();
}

float BoxCollider::GetFriction() const {
  return impl_->GetFriction();
}

void BoxCollider::SetFriction(float amount) {
  impl_->SetFriction(amount);
}

float BoxCollider::GetDensity() const {
  return impl_->GetDensity();
}

void BoxCollider::SetDensity(float amount) {
  impl_->SetDensity(amount);
}

bool BoxCollider::GetIsSensor() const {
  return impl_->GetIsSensor();
}

void BoxCollider::SetIsSensor(bool value) {
  impl_->SetIsSensor(value);
}

}