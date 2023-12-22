#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTER_H
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTER_H

#include "entities/component.h"
#include "particle.h"
#include <vector>
#include <memory>

namespace engine::entities {

/// Manages the emission of particles, controlling their behavior and rendering.
/// It serves as a base class for different types of particle systems, allowing for
/// customization of particle creation, update logic, and rendering.
class ParticleEmitter : public Component {
 public:
  /// Renders the particles using the provided sprite renderer.
  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<Transform> transform);

  /// Gets the currently active particles.
  std::vector<std::shared_ptr<Particle>> GetParticles();
  void AddParticle(std::shared_ptr<Particle> particle);
  void AddParticles(std::vector<std::shared_ptr<Particle>> particles);

  ParticleEmitter();
  virtual ~ParticleEmitter();
  void Start();
  void Stop();
  void SetDuration(float duration);
  float GetDuration() const;
  void SetLooping(bool looping);
  bool IsLooping() const;
  void SetEmissionInterval(float interval);
  float GetEmissionInterval() const;

 protected:
  /// Called for particle emission; implementation required in derived classes.
  virtual void OnEmit(float delta_time, Vector2d start_position) = 0;
  /// Optionally implemented in derived classes for updating active particles.
  virtual void UpdateActiveParticles(std::vector<std::shared_ptr<Particle>> particles) {};
  /// Optionally implemented in derived classes to handle particle deletion.
  virtual void OnParticleDeletion(std::shared_ptr<Particle> particle) {};
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

} // namespace engine::entities

#endif //ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTER_H
