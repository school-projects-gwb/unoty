#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_EXPLOSION_EMITTER_H
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_EXPLOSION_EMITTER_H

#include "utility/randomizer.h"
#include "particle_emitter.h"
#include <cmath>
#include <memory>

namespace engine::entities {

class ExplosionEmitter : public ParticleEmitter {
 public:
  explicit ExplosionEmitter(std::shared_ptr<Sprite> sprite,
                            int particle_amount,
                            float particle_speed,
                            float particle_lifespan)
      : ParticleEmitter(),
        sprite_(std::move(sprite)),
        particle_amount_(particle_amount),
        particle_speed_(particle_speed),
        particle_lifespan_(particle_lifespan) {
    SetLooping(false);
    SetEmissionInterval(1);
    SetDuration(1);
  }

  ~ExplosionEmitter() override = default;

 protected:
  void OnEmit(float delta_time, Vector2d start_position) override {
    float angle_increment = 2 * M_PI / particle_amount_;

    for (int i = 0; i < particle_amount_; i++) {
      float angle = i * angle_increment;
      Vector2d velocity = {std::cos(angle) * particle_speed_, std::sin(angle) * particle_speed_};

      auto transform = std::make_shared<Transform>();
      transform->Position = start_position;
      transform->SetSize({5, 5});

      auto particle = Component::Create<Particle>(velocity, particle_lifespan_, sprite_, transform);

      particle->SetUpdateCallback([this](Particle &p, float delta_time) {

      });

      AddParticle(particle);
    }
  }

 protected:
  std::shared_ptr<Sprite> sprite_;
  int particle_amount_;
  float particle_speed_;
  float particle_lifespan_;
};

} // namespace engine::entities

#endif //ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_EXPLOSION_EMITTER_H
