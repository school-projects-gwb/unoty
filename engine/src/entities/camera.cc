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
    tracking_transform_ = transform_to_track;
  }

  std::shared_ptr<Transform> GetTrackingTransform() {
    return tracking_transform_;
  }

  bool IsObjectInViewport(const std::shared_ptr<Transform>& object_transform, float offset, entities::Point camera_position) const {
    auto object_position = object_transform->GetCenterPosition();
    auto object_size = object_transform->GetScaledSize();

    bool overlaps_horizontally = (camera_position.x - offset <= object_position.x + object_size.x) &&
        (camera_position.x + engine::EngineConfig::window_width + offset >= object_position.x);

    bool overlaps_vertically = (camera_position.y - offset <= object_position.y + object_size.y) &&
        (camera_position.y + engine::EngineConfig::window_height + offset >= object_position.y);

    return overlaps_horizontally && overlaps_vertically;
  }

 private:
  Point position_;
  GameObject* owner_;
  std::shared_ptr<Transform> tracking_transform_;
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

}