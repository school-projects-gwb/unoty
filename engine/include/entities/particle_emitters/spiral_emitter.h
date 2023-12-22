#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_SPIRAL_EMITTER_H
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_SPIRAL_EMITTER_H

#include "particle_emitter.h"
#include <cmath>
#include <memory>

namespace engine::entities {

class SpiralEmitter : public ParticleEmitter {
 public:
  explicit SpiralEmitter(std::shared_ptr<Sprite> sprite, int particle_amount)
      : ParticleEmitter(), sprite_(std::move(sprite)), particle_amount_(particle_amount) {
    SetLooping(true);
    SetEmissionInterval(1);
    SetDuration(1);
  }

  ~SpiralEmitter() override = default;

 protected:
  void OnEmit(float delta_time, Vector2d start_position) override {
    float angle_increment = 2 * M_PI / particle_amount_;

    for (int i = 0; i < particle_amount_; i++) {
      float angle = i * angle_increment;
      Vector2d velocity = {std::cos(angle) * initial_speed_, std::sin(angle) * initial_speed_};

      auto transform = std::make_shared<Transform>();
      transform->Position = start_position;
      transform->SetSize({5, 5});

      auto particle = Component::Create<Particle>(velocity, lifespan_, sprite_, transform);

      particle->SetUpdateCallback([this, angle, start_position, accumulated_time = 0.0f](Particle &p, float delta_time) mutable {
        accumulated_time += delta_time;
        float spiral_angle = angle + rotation_speed_ * accumulated_time;
        float radius = initial_speed_ * accumulated_time * outward_speed_multiplier_;
        Vector2d new_position = {std::cos(spiral_angle) * radius, std::sin(spiral_angle) * radius};

        new_position.x += start_position.x;
        new_position.y += start_position.y;

        p.GetTransform()->Position = new_position;
      });
      AddParticle(particle);
    }
  }
 private:
  std::shared_ptr<Sprite> sprite_;
  int particle_amount_;
  float outward_speed_multiplier_ = 2.0;
  float initial_speed_ = 100; // Initial speed of the particles
  float lifespan_ = 3; // Lifespan of the particles
  float rotation_speed_ = 1; // Speed of rotation for the spiral effect
};

} // namespace engine::entities

#endif //ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_SPIRAL_EMITTER_H
