#include "entities/particle.h"
#include "utility/timer.h"

namespace engine::entities {

class Particle::Impl {
 public:
  Impl(const Vector2d& velocity, float lifespan, std::shared_ptr<Sprite> sprite, std::shared_ptr<Transform> transform)
      : velocity_(velocity), lifespan_(lifespan), sprite_(std::move(sprite)), transform_(std::move(transform)) {
    starting_position_ = transform_->Position;
  }

  void Update(float delta_time) {
    if (!IsAlive()) return;

    // Update position
    transform_->Position.x += velocity_.x * delta_time;
    transform_->Position.y += velocity_.y * delta_time;

    // Reduce lifespan
    lifespan_ -= delta_time;
  }

  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer) {
    sprite_->Render(renderer,transform_);
  }

  [[nodiscard]] bool IsAlive() const{
    return lifespan_ > 0;
  }

  [[nodiscard]] float GetLifespan() const{
    return lifespan_;
  }

  std::shared_ptr<Transform> GetTransform() {
    return transform_;
  }

  [[nodiscard]] Vector2d GetStartingPosition(){
    return starting_position_;
  }

  [[nodiscard]] Vector2d GetVelocity() const{
    return velocity_;
  }

  void SetVelocity(Vector2d velocity) {
    velocity_ = velocity;
  }

 private:
  Vector2d starting_position_;
  Vector2d velocity_;
  float lifespan_;
  std::shared_ptr<Sprite> sprite_;
  std::shared_ptr<Transform> transform_;
};

Particle::Particle(const Vector2d& velocity, float lifespan, std::shared_ptr<Sprite> sprite, std::shared_ptr<Transform> transform)
    : impl_(std::make_unique<Impl>(velocity, lifespan, std::move(sprite), std::move(transform))) {}

Particle::~Particle() = default;

void Particle::Render(const std::unique_ptr<ui::SpriteRenderer> &renderer, float delta_time) {
  impl_->Render(renderer);
  impl_->Update(delta_time);
}

bool Particle::IsAlive() const {
  return impl_->IsAlive();
}
float Particle::GetLifespan() const {
  return impl_->GetLifespan();
}
std::shared_ptr<Transform> Particle::GetTransform() {
  return impl_->GetTransform();
}
void Particle::SetVelocity(Vector2d velocity) {
  impl_->SetVelocity(velocity);
}
Vector2d Particle::GetVelocity() const {
  return impl_->GetVelocity();
}
Vector2d Particle::GetStartingPosition() const {
  return impl_->GetStartingPosition();
}

}