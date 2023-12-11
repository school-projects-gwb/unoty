#include <memory>
#include <iostream>
#include "entities/colliders/box_collider.h"
#include <box2d/box2d.h>

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

  float GetFriction() const
  {
    return friction_;
  }

  void SetFriction(float amount)
  {
    friction_ = amount;
  }

  float GetDensity() const
  {
    return density_;
  }

  void SetDensity(float amount)
  {
    density_ = amount;
  }

 private:
  Vector2d size_;
  float friction_ = 0.3f;
  float density_ = 1.0f;
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

float BoxCollider::GetFriction() const
{
  return impl_->GetFriction();
}

void BoxCollider::SetFriction(float amount)
{
  impl_->SetFriction(amount);
}

float BoxCollider::GetDensity() const
{
  return impl_->GetDensity();
}

void BoxCollider::SetDensity(float amount)
{
  impl_->SetDensity(amount);
}

}