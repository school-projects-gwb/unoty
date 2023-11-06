#include "entities/camera.h"
#include "helpers/debug.h"

namespace engine::entities {

class Camera::Impl : public GameObject {
 public:
  explicit Impl(GameObject* owner) : owner_(owner) {
    tracking_transform_ = owner_->GetTransform();
  }

  void UpdatePosition() {
    owner_->GetTransform()->Position = tracking_transform_->Position;
  }

  void SetBackgroundColor(Color color) {
    background_color_ = color;
  }

  void SetSize(Point size) {
    size_ = size;
  }

  void SetTrackingTransform(std::shared_ptr<Transform> transform_to_track) {
    tracking_transform_ = transform_to_track;
  }

  std::shared_ptr<Transform> GetTrackingTransform() {
    return tracking_transform_;
  }
 private:
  Color background_color_;
  Point size_ = {};
  GameObject* owner_;
  std::shared_ptr<Transform> tracking_transform_;
};

Camera::Camera() : impl_(std::make_unique<Impl>(this)) {}
Camera::~Camera() = default;

void Camera::UpdatePosition() {
  impl_->UpdatePosition();
}

void Camera::SetBackgroundColor(Color color) {
  impl_->SetBackgroundColor(color);
}

void Camera::SetSize(Point size) {
  impl_->SetSize(size);
}

void Camera::SetTrackingTransform(std::shared_ptr<Transform> transform_to_track) {
  impl_->SetTrackingTransform(transform_to_track);
}

std::shared_ptr<Transform> Camera::GetTrackingTransform() {
  return impl_->GetTrackingTransform();
}

}