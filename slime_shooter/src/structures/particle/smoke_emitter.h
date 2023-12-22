#ifndef SLIME_SHOOTER_SRC_WORLD_PARTICLE_SINE_EMITTER_H
#define SLIME_SHOOTER_SRC_WORLD_PARTICLE_SINE_EMITTER_H

#include "entities/particle_emitters/particle_emitter.h"
#include "utility/randomizer.h"
#include <cmath>
#include <memory>

namespace slime_shooter {

using namespace engine::entities;

// SmokeEmitter to test the particle emitter
class SmokeEmitter : public ParticleEmitter {
 public:
  SmokeEmitter()
      : ParticleEmitter() {
    SetDuration(0);
    SetLooping(true);
    SetEmissionInterval(1);

    sprite_ = Component::Create<Sprite>("resources/sprites/world/particle_orange.png");
  }

  ~SmokeEmitter() override = default;

 protected:
  void OnEmit(float delta_time, Vector2d start_position) override {
    int particle_amount = engine::utility::Randomizer::GetInstance().RandomInt(5, 20);
    start_position.x += 115.0f;
    start_position.y += 125.0f;

    for(int i = 0; i < particle_amount; i++) {
      int random_speed = engine::utility::Randomizer::GetInstance().RandomInt(-5, 5);
      Vector2d velocity(random_speed, (-25 + random_speed));

      auto transform = std::make_shared<Transform>();

      auto random_x = engine::utility::Randomizer::GetInstance().RandomFloat(-10.0f, 10.0f);
      auto random_y = engine::utility::Randomizer::GetInstance().RandomFloat(-10.0f, 10.0f);

      transform->Position = {start_position.x + random_x, start_position.y + random_y};
      transform->SetSize({10,10});

      auto particle = Component::Create<Particle>(velocity, 5, sprite_, transform);

      particle->SetUpdateCallback([this](Particle& p, float delta_time) {
        auto starting_position = p.GetStartingPosition();
        auto position = p.GetTransform()->Position;
        Vector2d velocity = p.GetVelocity();

        if (position.x <= (starting_position.x - boundary) || position.x >= (starting_position.x + boundary)) {
          velocity.x = -velocity.x;
        }

        p.SetVelocity(velocity);
      });

      AddParticle(particle);
    }
  }

 private:
  float boundary = 7.5;
  std::shared_ptr<Sprite> sprite_;
};

} // namespace slime_shooter

#endif //SLIME_SHOOTER_SRC_WORLD_PARTICLE_SINE_EMITTER_H
