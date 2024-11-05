#include <utility>

#include "entities/camera.h"
#include "utility/debug.h"
#include "engine/engine_config.h"

namespace engine::entities {

class Camera::Impl : public GameObject {
 public:
  explicit Impl(GameObject* owner) : owner_(owner) {
    tracking_transform_ = owner_->GetTransform();
  }

  void UpdatePosition() {
    owner_->GetTransform()->Position = tracking_transform_->Position;
  }

  void SetPosition(Point position) {
    position_ = position;
  }

  Point GetPosition(bool with_offset) const {
    return position_;
  }

  void SetTrackingTransform(std::shared_ptr<Transform> transform_to_track) {
    has_tracking_transform_ = true;
    tracking_transform_ = std::move(transform_to_track);
  }

  std::shared_ptr<Transform> GetTrackingTransform() {
    return tracking_transform_;
  }

  [[nodiscard]] bool HasTrackingTransform() const {
    return has_tracking_transform_;
  }

  bool IsObjectInViewport(const std::shared_ptr<Transform>& object_transform, float offset, entities::Point camera_position) const {
    // Get object position and size
    auto object_position = object_transform->GetCenterPosition();
    auto object_size = object_transform->GetScaledSize();

    // Adjust object position to account for its top-left corner (instead of center)
    auto object_top_left_x = object_position.x - (object_size.x / 2);
    auto object_top_left_y = object_position.y - (object_size.y / 2);

    // Calculate the camera's viewport bounds
    float camera_left = camera_position.x - offset;
    float camera_right = camera_position.x + engine::EngineConfig::window_width + offset;
    float camera_top = camera_position.y - offset;
    float camera_bottom = camera_position.y + engine::EngineConfig::window_height + offset;

    // Check horizontal overlap
    bool overlaps_horizontally = (camera_left <= object_top_left_x + object_size.x) &&
                                 (camera_right >= object_top_left_x);

    // Check vertical overlap
    bool overlaps_vertically = (camera_top <= object_top_left_y + object_size.y) &&
                               (camera_bottom >= object_top_left_y);

    return overlaps_horizontally && overlaps_vertically;
  }


 private:
  Point position_;
  GameObject* owner_;
  std::shared_ptr<Transform> tracking_transform_;
  bool has_tracking_transform_ = false;
};

Camera::Camera() : impl_(std::make_unique<Impl>(this)) {}
Camera::~Camera() = default;

void Camera::UpdatePosition() {
  impl_->UpdatePosition();
}

void Camera::SetTrackingTransform(std::shared_ptr<Transform> transform_to_track) {
  impl_->SetTrackingTransform(transform_to_track);
}

std::shared_ptr<Transform> Camera::GetTrackingTransform() {
  return impl_->GetTrackingTransform();
}

bool Camera::IsObjectInViewport(const std::shared_ptr<Transform> &object_transform, float offset, Point camera_position) {
  return impl_->IsObjectInViewport(object_transform, offset, camera_position);
}

void Camera::SetPosition(Point position) {
  return impl_->SetPosition(position);
}

Point Camera::GetPosition(bool with_offset) const {
  return impl_->GetPosition(with_offset);
}

bool Camera::HasTrackingTransform() const {
  return impl_->HasTrackingTransform();
}

}