#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_H_
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_H_

#include "component.h"
#include "sprite.h"
#include "transform.h"
#include "entities/structs/precise_point.h"
#include <memory>

namespace engine::entities {
/// Represents a single particle in a particle collection.
/// Handles the properties and behaviors of a particle, including
/// its motion, rendering, and lifespan.
class Particle : public Component {
 public:
  /// Constructs a particle with initial properties.
  /// @param velocity The initial velocity of the particle.
  /// @param lifespan The lifespan of the particle in seconds.
  /// @param sprite The sprite used to render the particle.
  /// @param transform The transformation applied to the particle.
  Particle(const Vector2d& velocity, float lifespan, std::shared_ptr<Sprite> sprite, std::shared_ptr<Transform> transform);
  ~Particle() override;

  /// Renders the particle using the provided sprite renderer.
  /// @param renderer The renderer used to draw the particle's sprite.
  /// @oaram delta_time Time used to move forward
  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, float delta_time);

  /// Checks if the particle is still alive based on its lifespan.
  /// @return True if the particle's lifespan is greater than zero, false otherwise.
  [[nodiscard]] bool IsAlive() const;

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
