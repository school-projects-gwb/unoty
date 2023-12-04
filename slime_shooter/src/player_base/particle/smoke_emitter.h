#ifndef SLIME_SHOOTER_SRC_WORLD_PARTICLE_SINE_EMITTER_H
#define SLIME_SHOOTER_SRC_WORLD_PARTICLE_SINE_EMITTER_H

#include "entities/particle_emitter.h"
#include "utility/randomizer.h"
#include <cmath>
#include <memory>

namespace slime_shooter {

using namespace engine::entities;

// SmokeEmitter to test the particle emitter
class SmokeEmitter : public ParticleEmitter {
 public:
  // Constructor
  SmokeEmitter()
      : ParticleEmitter() { // Adjust boundaries as needed
    SetDuration(0);
    SetLooping(false);
    SetEmissionInterval(1);

    // create sprite for all particles
    sprite_ = Component::Create<Sprite>("resources/sprites/world/particle_orange.png");
  }

  ~SmokeEmitter() override = default;

 protected:
  // Override to create smoke-specific particles
  std::vector<std::shared_ptr<Particle>> CreateParticles(float delta_time, Vector2d start_position) override {
    std::vector<std::shared_ptr<Particle>> new_particles;
    int particle_amount = Randomizer::GetInstance().RandomInt(5, 20);

    new_particles.reserve(particle_amount);
    start_position.x += 115.0f;
    start_position.y += 125.0f;

    for(int i = 0; i < particle_amount; i++) {
      int random_speed = Randomizer::GetInstance().RandomInt(-5, 5);
      Vector2d velocity(random_speed, (-25 + random_speed));

      auto transform = std::make_shared<Transform>();

      auto random_x = Randomizer::GetInstance().RandomFloat(-10.0f, 10.0f);
      auto random_y = Randomizer::GetInstance().RandomFloat(-10.0f, 10.0f);

      transform->Position = {start_position.x + random_x, start_position.y + random_y};
      transform->SetSize({10,10});

      new_particles.push_back(Component::Create<Particle>(velocity, 8, sprite_, transform));
    }

    return new_particles;
  }

  void UpdateActiveParticles(std::vector<std::shared_ptr<Particle>> particles) override {
    for (auto& particle : particles) {
      auto starting_position = particle->GetStartingPosition();
      auto position = particle->GetTransform()->Position;
      Vector2d velocity = particle->GetVelocity();

      // Reverse horizontal direction at boundaries
      if (position.x <= (starting_position.x-boundary) || position.x >= (starting_position.x+boundary)) {
        velocity.x = -velocity.x;
      }

      particle->SetVelocity(velocity);
    }
  }

  void OnParticleDeletion(std::shared_ptr<Particle> particle) override {

  }

 private:
  float boundary = 7.5;
  std::shared_ptr<Sprite> sprite_;
};

} // namespace slime_shooter

#endif //SLIME_SHOOTER_SRC_WORLD_PARTICLE_SINE_EMITTER_H
