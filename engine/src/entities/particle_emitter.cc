#include "entities/particle_emitters/particle_emitter.h"
#include "utility/timer.h"
#include <algorithm>
#include <utility>

namespace engine::entities {

class ParticleEmitter::Impl {
 public:
  Impl() : timer_(), delta_time_(0.0), emitting_(false), duration_(5.0), emission_accumulator_(0.0),
        looping_(false), emission_interval_(1.0), elapsed_time_(0.0) {}

  void Update(const std::shared_ptr<Transform>& transform, ParticleEmitter& emitter) {
    delta_time_ = GetDeltaTime();
    HandleEmission(transform, emitter);
    UpdateDuration();
    emitter.UpdateActiveParticles(particles_);
    RemoveInactiveParticles(emitter);
  }

  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<Transform>& transform) {
    for (const auto& particle : particles_) {
      particle->Render(renderer, delta_time_);
    }
  }

  std::vector<std::shared_ptr<Particle>> GetParticles() {
    return particles_;
  }

  void Start() {
    emitting_ = true;
    timer_.Start();
    elapsed_time_ = 0;
    emission_accumulator_ = emission_interval_;
  }

  void Stop() {
    emitting_ = false;
  }

  void SetDuration(float duration) {
    duration_ = duration;
  }

  [[nodiscard]] float GetDuration() const {
    return duration_;
  }

  void SetLooping(bool looping) {
    looping_ = looping;
    if(looping_){
      timer_.Start();
    }
  }

  [[nodiscard]] bool IsLooping() const {
    return looping_;
  }

  void SetEmissionInterval(float interval) {
    emission_interval_ = interval;
  }

  [[nodiscard]] float GetEmissionInterval() const {
    return emission_interval_;
  }

  void AddParticle(std::shared_ptr<Particle> particle) {
    particles_.push_back(std::move(particle));
  }

  void AddParticles(std::vector<std::shared_ptr<Particle>> particles) {
    particles_.insert(particles_.end(), particles.begin(), particles.end());
  }

 private:
  std::shared_ptr<Sprite> sprite_;
  std::vector<std::shared_ptr<Particle>> particles_;
  engine::utility::Timer timer_;
  float delta_time_;
  bool emitting_;
  float duration_;
  float emission_accumulator_;
  bool looping_;
  float emission_interval_;
  float elapsed_time_;

  float GetDeltaTime() {
    delta_time_ = static_cast<float>(timer_.GetElapsedSeconds());
    timer_.Start();
    return delta_time_;
  }

  void HandleEmission(const std::shared_ptr<Transform>& transform, ParticleEmitter& emitter) {
    if (emitting_) {
      emission_accumulator_ += delta_time_;

      while (emission_accumulator_ >= emission_interval_) {
        emission_accumulator_ -= emission_interval_;
        emitter.OnEmit(emission_interval_, transform->Position);
      }
    }
  }

  void UpdateDuration() {
    if (emitting_ && !looping_) {
      if (duration_ > 0) {
        elapsed_time_ += delta_time_;
        if (elapsed_time_ >= duration_) {
          Stop();
        }
      } else if (duration_ == 0) {
        Stop();
      }
    }
  }

  void RemoveInactiveParticles(ParticleEmitter& emitter) {
    std::vector<std::shared_ptr<Particle>> particles_to_delete;

    for (const auto& particle : particles_) {
      if (!particle->IsAlive()) {
        particles_to_delete.push_back(particle);
      }
    }

    particles_.erase(std::remove_if(particles_.begin(), particles_.end(),
                                    [&](const auto& particle) {
                                      return std::find(particles_to_delete.begin(), particles_to_delete.end(), particle) != particles_to_delete.end();
                                    }), particles_.end());

    for (const auto& particle : particles_to_delete) {
      emitter.OnParticleDeletion(particle);
    }
  }

};
ParticleEmitter::ParticleEmitter()
    : impl_(std::make_unique<Impl>()) {}

ParticleEmitter::~ParticleEmitter() = default;

void ParticleEmitter::Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<Transform> transform) {
  impl_->Render(renderer, transform);
  impl_->Update(transform, *this);
}

void ParticleEmitter::Start() {
  impl_->Start();
}

void ParticleEmitter::Stop() {
  impl_->Stop();
}

void ParticleEmitter::SetDuration(float duration) {
  impl_->SetDuration(duration);
}

float ParticleEmitter::GetDuration() const{
  return impl_->GetDuration();
}

void ParticleEmitter::SetLooping(bool looping) {
  impl_->SetLooping(looping);
}

bool ParticleEmitter::IsLooping() const {
  return impl_->IsLooping();
}

std::vector<std::shared_ptr<Particle>> ParticleEmitter::GetParticles() {
  return impl_->GetParticles();
}
void ParticleEmitter::SetEmissionInterval(float interval) {
  impl_->SetEmissionInterval(interval);
}
float ParticleEmitter::GetEmissionInterval() const {
  return impl_->GetEmissionInterval();
}
void ParticleEmitter::AddParticle(std::shared_ptr<Particle> particle) {
  impl_->AddParticle(std::move(particle));
}
void ParticleEmitter::AddParticles(std::vector<std::shared_ptr<Particle>> particles) {
  impl_->AddParticles(std::move(particles));
}

}