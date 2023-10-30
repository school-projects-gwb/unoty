#include "entities/camera.h"
namespace engine::entities {

class Camera::Impl {
 public:
  Impl() {}

  void SetBackgroundColor(Color color) {
    background_color_ = color;
  }

  void SetSize(Point size) {
    size_ = size;
  }

 private:
  Color background_color_;
  Point size_;
};

Camera::Camera() : impl_(std::make_unique<Impl>()) {}
Camera::~Camera() = default;

void Camera::SetBackgroundColor(Color color) {
  impl_->SetBackgroundColor(color);
}

void Camera::SetSize(Point size) {
  impl_->SetSize(size);
}

}