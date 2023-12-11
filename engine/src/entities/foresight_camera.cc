#include "entities/camera.h"
#include "entities/foresight_camera.h"

namespace engine::entities {

class ForesightCamera::Impl : public Camera {
 public:
  explicit Impl(Camera *owner, float offset_max_size, float offset_velocity) :
      owner_(owner), offset_max_size_(offset_max_size), velocity_(offset_velocity) {
    previous_location_ = owner_->GetTransform()->Position;
    current_offset_ = Vector2d{0, 0};
  }

  void SetPosition(Point position) override {
    position_ = position;
  }

  Point GetPosition(bool with_offset) const override {
    if (!with_offset)
      return Point{position_.x - (int)current_offset_.x, position_.y - (int)current_offset_.y};
    else
      return position_;
  }

  void UpdatePosition() override {
    Vector2d current_location = owner_->GetTrackingTransform()->Position;
    Vector2d looking_direction = GetLookingDirection(current_location);

    UpdateOffset(looking_direction);

    Vector2d new_camera_position = previous_location_ + current_offset_;
    owner_->GetTransform()->Position = new_camera_position;

    previous_location_ = current_location;
  }

 private:
  Point position_;
  Camera *owner_;
  Vector2d previous_location_;
  Vector2d current_offset_;
  float offset_max_size_;
  float velocity_;

  Vector2d GetLookingDirection(Vector2d target) {
    Vector2d direction;

    direction.x = target.x - previous_location_.x;
    direction.y = target.y - previous_location_.y;

    direction.Normalize();

    return direction;
  }

  void UpdateOffset(const Vector2d &looking_direction) {
    if (looking_direction.x != 0) {
      current_offset_.x += looking_direction.x * velocity_;
    }
    if (looking_direction.y != 0) {
      current_offset_.y += looking_direction.y * velocity_;
    }

    current_offset_.x = std::clamp(current_offset_.x, -offset_max_size_, offset_max_size_);
    current_offset_.y = std::clamp(current_offset_.y, -offset_max_size_, offset_max_size_);

    if (looking_direction.x == 0 && looking_direction.y == 0) {
      current_offset_.x = approach(current_offset_.x, 0, velocity_);
      current_offset_.y = approach(current_offset_.y, 0, velocity_);
    }
  }

  float approach(float value, float target, float increment) {
    if (value < target) {
      return std::min(value + increment, target);
    } else {
      return std::max(value - increment, target);
    }
  }
};

ForesightCamera::ForesightCamera(float offset_max_size, float offset_velocity) :
    impl_(std::make_unique<Impl>(this, offset_max_size, offset_velocity)) {}

ForesightCamera::~ForesightCamera() = default;

void ForesightCamera::UpdatePosition() {
  impl_->UpdatePosition();
}

void ForesightCamera::SetPosition(Point position) {
  impl_->SetPosition(position);
}

Point ForesightCamera::GetPosition(bool with_offset) const {
  return impl_->GetPosition(with_offset);
}

}
