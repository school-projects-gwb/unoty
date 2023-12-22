#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_FIREWORK_EMITTER_H
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_FIREWORK_EMITTER_H

#include "particle_emitter.h"
#include "firework_particle.h"
#include "utility/randomizer.h"

namespace engine::entities {

class FireworkEmitter : public ParticleEmitter {
 public:
  explicit FireworkEmitter(std::shared_ptr<Sprite> sprite, int particle_amount, int max_generation, int speed_distance)
      : ParticleEmitter(),
        sprite_(std::move(sprite)),
        particle_amount_(particle_amount),
        speed_distance_(speed_distance),
        max_generation_(max_generation) {
  }

  ~FireworkEmitter() override = default;

 protected:
  void OnEmit(float delta_time, Vector2d start_position) override {
    float angle_increment = 2 * M_PI / particle_amount_;

    for (int i = 0; i < particle_amount_; i++) {
      float angle = i * angle_increment;
      Vector2d velocity = {std::cos(angle) * speed_distance_, std::sin(angle) * speed_distance_};

      auto transform = std::make_shared<Transform>();
      transform->Position = start_position;
      transform->SetSize({5, 5});

      AddParticle(Component::Create<FireworkParticle>(velocity, 1, sprite_, transform, 1));
    }
  }

  void OnParticleDeletion(std::shared_ptr<Particle> particle) override {
    auto firework_particle = std::dynamic_pointer_cast<FireworkParticle>(particle);

    if (firework_particle) {
      int generation = firework_particle->GetGeneration();

      if (generation < max_generation_) {
        float chance_for_offspring = 0.5 * std::pow(0.25, generation - 1);
        float random_chance = engine::utility::Randomizer::GetInstance().RandomFloat(0.0f, 1.0f);

        if (random_chance <= chance_for_offspring) {
          auto secondary_particles = CreateSecondaryParticles(firework_particle->GetTransform()->Position, generation);
          AddParticles(secondary_particles);
        }
      }
    }
  }

 protected:
  std::shared_ptr<Sprite> sprite_;
  int particle_amount_;
  int speed_distance_;
  int max_generation_;

 private:
  std::vector<std::shared_ptr<Particle>> CreateSecondaryParticles(Vector2d position, int parent_generation) {
    std::vector<std::shared_ptr<Particle>> secondary_particles;

    int final_particle_count = particle_amount_ / parent_generation;
    float angle_increment = 2 * M_PI / final_particle_count;

    for (int i = 0; i < final_particle_count; i++) {
      float angle = i * angle_increment;
      Vector2d velocity = {std::cos(angle) * (speed_distance_ / (parent_generation + 1)),
                           std::sin(angle) * (speed_distance_ / (parent_generation + 1))};

      auto transform = std::make_shared<Transform>();
      transform->Position = position;
      transform->SetSize({5, 5});

      auto secondary_particle = std::make_shared<FireworkParticle>(
          velocity, 1, sprite_, transform, parent_generation + 1
      );

      secondary_particles.push_back(secondary_particle);
    }

    return secondary_particles;
  }
};

}

#endif //ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_FIREWORK_EMITTER_H
