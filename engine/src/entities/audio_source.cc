#include "entities/audio_source.h"
#include "utility/path_helper.h"
#include "audio/audio_factory_wrapper.h"

namespace engine::entities {

class AudioSource::Impl : public Component {
 public:
  explicit Impl(const std::string &track) {
    auto p = helpers::PathHelper::GetFullPathFromRelative(track);
    audio_ = engine::audio::AudioFactoryWrapper::get_instance().CreateAudio(p);
  }
  ~Impl() override{
    delete audio_;
  }

  void Play() { audio_->Stop(); audio_->Play(); }
  void Stop() { audio_->Stop(); }

  void TogglePaused() { audio_->TogglePaused(); }
  bool IsPaused() { return audio_->IsPaused(); }
  void ToggleLooping() { audio_->Stop(); audio_->loop_ = !audio_->loop_; }
  bool IsLooping() { return audio_->loop_; }

  void SetVolume(int volume) { audio_->SetVolume(volume); }
  int GetVolume() { return audio_->GetVolume(); }
  void SetPitch(int pitch) { audio_->SetPitch(pitch); }
  int GetPitch() { return audio_->GetPitch(); }
  void SetSpeed(int speed) { audio_->SetSpeed(speed); }
  int GetSpeed() { return audio_->GetSpeed(); }

 private:
  Audio* audio_;
};

AudioSource::~AudioSource() = default;
AudioSource::AudioSource(const std::string &track) : impl_(std::make_unique<Impl>(track)) { }

void AudioSource::Play() { impl_->Play(); }
void AudioSource::Stop() { impl_->Stop(); }

void AudioSource::TogglePaused() { impl_->TogglePaused(); }
bool AudioSource::IsPaused() { return impl_->IsPaused(); }

/// @warning This toggle function will stop the audio if it is playing.
void AudioSource::ToggleLooping() { impl_->ToggleLooping(); }
bool AudioSource::IsLooping() { return impl_->IsLooping(); }

/// @brief Sets the volume based on a percentage value. (default = 100)
/// @param x Parameter description
void AudioSource::SetVolume(int volume) { impl_->SetVolume(volume); }
int AudioSource::GetVolume() { return impl_->GetVolume(); }
void AudioSource::SetPitch(int pitch) { impl_->SetPitch(pitch); }
int AudioSource::GetPitch() { return impl_->GetPitch(); }
void AudioSource::SetSpeed(int speed) { impl_->SetSpeed(speed); }
int AudioSource::GetSpeed() { return impl_->GetSpeed(); }
}