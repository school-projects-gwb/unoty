#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_FIREWORK_PARTICLE_H
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_FIREWORK_PARTICLE_H

#include "particle.h"

namespace engine::entities {

class FireworkParticle : public Particle {
 public:
  FireworkParticle(const Vector2d& velocity, float lifespan, std::shared_ptr<Sprite> sprite, std::shared_ptr<Transform> transform, int generation)
      : Particle(velocity, lifespan, std::move(sprite), std::move(transform)), generation_(generation) {}

  int GetGeneration() const { return generation_; }
  void SetGeneration(int generation) { generation_ = generation; }

 private:
  int generation_;
};


}

#endif //ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTERS_FIREWORK_PARTICLE_H
