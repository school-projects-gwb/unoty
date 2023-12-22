
#include "entities/artificial_intelligence/circle_path_around_object_ai.h"
#include "engine/engine.h"
#include "ai_base.h"

namespace engine::entities {

class CircleAroundObjectAI::Impl : public AIBase {
 public:
  Impl() { };
  ~Impl() override { }

  [[nodiscard]] std::shared_ptr<Transform> GetNewPosition() override {
    position_->Position.x = (distance_ * std::sin(angle_)) + target_->Position.x - static_cast<float>(target_->GetSize().x);
    position_->Position.y = (distance_ * std::cos(angle_)) + target_->Position.y - static_cast<float>(target_->GetSize().y);

    angle_ += speed_;
    if (angle_ > 360.0f) angle_ -= 360.0f;
    else if (angle_ < 0.0f) angle_ += 360.0f;

    position_->SetRotation(this_->GetRotation() + rotation_speed_);
    position_->SetScale(this_->GetScale());

    return position_;
  }

  void SetTarget(GameObject *target) {
    target_ = target->GetTransform();
  }

  float distance_ = 50.0f;
  float speed_ = 1.0f;
  float angle_ = 0.0f;
  float rotation_speed_ = 0.0f;
 private:
  std::shared_ptr<Transform> target_;
};

CircleAroundObjectAI::~CircleAroundObjectAI() = default;
CircleAroundObjectAI::CircleAroundObjectAI() : impl_(std::make_unique<Impl>()) { }

std::shared_ptr<Transform> CircleAroundObjectAI::GetNewPosition() {
  return impl_->GetNewPosition();
}

void CircleAroundObjectAI::Init(GameObject *target) {
  SetTarget(target);
  impl_->Init(this->GetGameObject().GetTransform());
}
void CircleAroundObjectAI::SetTarget(GameObject *target) {
  impl_->SetTarget(target);
}
float CircleAroundObjectAI::GetDistance() {
  return impl_->distance_;
}
float CircleAroundObjectAI::GetSpeed() {
  return impl_->speed_;
}
float CircleAroundObjectAI::GetAngle() {
  return impl_->angle_;
}
float CircleAroundObjectAI::GetRotationSpeed() {
  return impl_->rotation_speed_;
}

void CircleAroundObjectAI::SetDistance(float val) {
  impl_->distance_ = val;
}
void CircleAroundObjectAI::SetSpeed(float val) {
  impl_->speed_ = val;
}
void CircleAroundObjectAI::SetAngle(float val) {
  impl_->angle_ = val;
}
void CircleAroundObjectAI::SetRotationSpeed(float val) {
  impl_->rotation_speed_ = val;
}
}