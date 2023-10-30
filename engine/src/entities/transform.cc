#include "entities/transform.h"
namespace engine::entities {

class Transform::Impl {
 public:
  Impl() {}

  void SetRotation(float rotation) {
    rotation_ = rotation;
  }

  float GetRotation() {
    return rotation_;
  }

  void SetScale(float scale) {
    scale_ = scale;
  }

  float GetScale() {
    return scale_;
  }

 private:
  float scale_ = 1;
  float rotation_ = 0.0;
};

Transform::Transform() : impl_(new Impl()) {}
Transform::~Transform() = default;

void Transform::SetRotation(float rotation) {
  impl_->SetRotation(rotation);
}

float Transform::GetRotation() {
  return impl_->GetRotation();
}

void Transform::SetScale(float scale) {
  impl_->SetScale(scale);
}

float Transform::GetScale() {
  return impl_->GetScale();
}

}