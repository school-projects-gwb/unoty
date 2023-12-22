#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_H_
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_H_

#include "entities/component.h"
#include "entities/sprite.h"
#include "entities/transform.h"
#include <functional>
#include "entities/structs/precise_point.h"
#include <memory>

namespace engine::entities {
/// Represents a single particle in a particle collection.
/// Handles the properties and behaviors of a particle, including
/// its motion, rendering, and lifespan.
class Particle : public Component {
 public:
  using ParticleUpdateCallback = std::function<void(Particle&, float delta_time)>;
  /// Constructs a particle with initial properties.
  Particle(const Vector2d& velocity, float lifespan, std::shared_ptr<Sprite> sprite, std::shared_ptr<Transform> transform);
  ~Particle() override;

  /// Renders the particle using the provided sprite renderer.
  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, float delta_time);

  /// Checks if the particle is still alive based on its lifespan.
  [[nodiscard]] bool IsAlive() const;

  /// Sets a callback function that will be called during the particle update.
  void SetUpdateCallback(const ParticleUpdateCallback& callback);

  [[nodiscard]] float GetLifespan() const;
  std::shared_ptr<Transform> GetTransform();
  [[nodiscard]] Vector2d GetStartingPosition() const;
  [[nodiscard]] Vector2d GetVelocity() const;
  void SetVelocity(Vector2d velocity);

 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif  // ENGINE_INCLUDE_ENTITIES_PARTICLE_H_
