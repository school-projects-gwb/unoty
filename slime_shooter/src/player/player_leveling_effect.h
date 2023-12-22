#ifndef SLIME_SHOOTER_SRC_PLAYER_PLAYER_LEVELING_EFFECT_H
#define SLIME_SHOOTER_SRC_PLAYER_PLAYER_LEVELING_EFFECT_H

#include "entities/particle_emitters/particle_emitter.h"
#include "utility/randomizer.h"
#include <memory>

using namespace engine::entities;

namespace slime_shooter {

class PlayerLevelingEffect : public ParticleEmitter {
 public:
  explicit PlayerLevelingEffect(int particle_amount, Vector2d offset, Point size)
      : ParticleEmitter(),
        sprite_(Component::Create<Sprite>("resources/sprites/world/particle.png")),
        particle_amount_(particle_amount),
        offset_(offset),
        size_(size) {
    SetLooping(false);
    SetEmissionInterval(0.1);
    SetDuration(0.15);
  }

  ~PlayerLevelingEffect() override = default;

 protected:
  void OnEmit(float delta_time, Vector2d start_position) override {
    for (int i = 0; i < particle_amount_; ++i) {
      Vector2d initial_velocity = {0, -10};

      auto rand_offset_x = engine::utility::Randomizer::GetInstance().RandomFloat(0, size_.x);
      auto rand_offset_y = engine::utility::Randomizer::GetInstance().RandomFloat(0, size_.y);

      auto transform = std::make_shared<Transform>();

      transform->Position = {
          start_position.x + offset_.x + rand_offset_x,
          start_position.y + offset_.y + rand_offset_y
      };

      transform->SetSize({10, 10});
      auto particle = Component::Create<Particle>(initial_velocity, lifespan_, sprite_, transform);

      particle->SetUpdateCallback([max_y = start_position.y + offset_.y](Particle &p, float delta_time) {
        if(p.GetTransform()->Position.y <= max_y){
          p.SetVelocity({0,0});
        }
      });

      AddParticle(particle);
    }
  }

 private:
  std::shared_ptr<Sprite> sprite_;
  int particle_amount_;
  float lifespan_ = 1;
  Vector2d offset_;
  Point size_;
};

} // namespace slime_shooter


#endif //SLIME_SHOOTER_SRC_PLAYER_PLAYER_LEVELING_EFFECT_H
