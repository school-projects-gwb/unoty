#include "entities/transform.h"
#include "utility/debug.h"
namespace engine::entities {

class Transform::Impl {
 public:
  Impl() = default;

  Impl(float rotation, float scale) : rotation_(rotation), scale_(scale) {}

  void SetRotation(float rotation) {
    float min_rotation = 0.0;
    float max_rotation = 360.0;

    // Rotation is in bounds of allowed rotation values
    if (rotation >= min_rotation && rotation <= max_rotation) {
      rotation_ = rotation;
      return;
    }

    // Set rotation to minimum/maximum allowed value
    rotation_ = rotation < min_rotation ? min_rotation : max_rotation;
  }

  [[nodiscard]] entities::Point GetScaledSize() const {
    return {static_cast<int>(static_cast<float>(size_.x) * scale_),
            static_cast<int>(static_cast<float>(size_.y) * scale_)};
  }

  [[nodiscard]] float GetRotation() const {
    return rotation_;
  }

  void SetScale(float scale) {
    scale_ = scale;
  }

  [[nodiscard]] float GetScale() const {
    return scale_;
  }

  void SetSize(entities::Point size) {
    size_ = size;
  }

  [[nodiscard]] entities::Point GetSize() const {
    return size_;
  }

 private:
  float rotation_ = 0.0;
  float scale_ = 1;
  entities::Point size_{0, 0};
};

Transform::Transform() : impl_(new Impl()) {}
Transform::Transform(engine::entities::Vector2d position, float rotation, float scale)
    : impl_(new Impl(rotation, scale)) {
  Position = position;
}

Transform::~Transform() = default;

void Transform::SetRotation(float rotation) {
  impl_->SetRotation(rotation);
}

float Transform::GetRotation() const {
  return impl_->GetRotation();
}

void Transform::SetScale(float scale) {
  impl_->SetScale(scale);
}

float Transform::GetScale() const {
  return impl_->GetScale();
}

void Transform::SetSize(entities::Point size) {
  impl_->SetSize(size);
}

entities::Point Transform::GetSize() const {
  return impl_->GetSize();
}
entities::Point Transform::GetScaledSize() const {
  return impl_->GetScaledSize();
}

}