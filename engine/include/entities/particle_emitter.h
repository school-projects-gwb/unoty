#ifndef ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTER_H
#define ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTER_H

#include "component.h"
#include "particle.h"
#include <vector>
#include <memory>

namespace engine::entities {

/// Manages the emission of particles, controlling their behavior and rendering.
/// It serves as a base class for different types of particle systems, allowing for
/// customization of particle creation, update logic, and rendering.
class ParticleEmitter : public Component {
 public:
  /// Constructs a ParticleEmitter.
  ParticleEmitter();

  /// Destructor for ParticleEmitter.
  virtual ~ParticleEmitter();

  /// Renders the particles using the provided sprite renderer.
  /// @param renderer The sprite renderer to draw particles.
  /// @param transform The transformation applied to the particle system.
  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<Transform> transform);

  /// Starts the particle emission.
  void Start();

  /// Stops the particle emission.
  void Stop();

  /// Sets the duration of the particle emission.
  /// @param duration The duration in seconds for which particles are emitted.
  void SetDuration(float duration);

  /// Retrieves the duration of the particle emission.
  /// @return The duration in seconds.
  float GetDuration();

  /// Sets whether the particle emission should loop.
  /// @param looping True to make the emission loop, false otherwise.
  void SetLooping(bool looping);

  /// Checks if the particle emission is set to loop.
  /// @return True if looping is enabled, false otherwise.
  bool IsLooping();

  /// Sets the interval between particle emissions.
  /// @param interval The time in seconds between emissions.
  void SetEmissionInterval(float interval);

  /// Retrieves the interval between particle emissions.
  /// @return The emission interval in seconds.
  float GetEmissionInterval();

  /// Gets the currently active particles.
  /// @return A vector of shared pointers to the active particles.
  std::vector<std::shared_ptr<Particle>> GetParticles();

 protected:
  /// Creates particles to be emitted. Must be implemented in derived classes.
  /// @param delta_time The time elapsed since the last update.
  /// @param start_position The starting position for the particles.
  /// @return A vector of shared pointers to the newly created particles.
  virtual std::vector<std::shared_ptr<Particle>> CreateParticles(float delta_time, Vector2d start_position) = 0;

  /// Updates the active particles. Must be implemented in derived classes.
  /// @param particles The list of currently active particles to be updated.
  virtual void UpdateActiveParticles(std::vector<std::shared_ptr<Particle>> particles) = 0;

  /// Handles the deletion of a particle. Must be implemented in derived classes.
  /// @param particle The particle that is to be deleted.
  virtual void OnParticleDeletion(std::shared_ptr<Particle> particle) = 0;

 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

} // namespace engine::entities

#endif //ENGINE_INCLUDE_ENTITIES_PARTICLE_EMITTER_H
