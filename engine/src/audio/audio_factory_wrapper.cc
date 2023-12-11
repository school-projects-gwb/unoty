#include "audio_factory_wrapper.h"

namespace engine::audio {

AudioFactoryWrapper &AudioFactoryWrapper::GetInstance() {
  static AudioFactoryWrapper instance;
  return instance;
}

void AudioFactoryWrapper::SetAudioFactory(std::unique_ptr<AudioFactoryBase> base) {
  audio_factory_base_ = std::move(base);
}

Audio *AudioFactoryWrapper::CreateAudio(const std::string &file_path) {
  return audio_factory_base_->CreateAudio(file_path, engine::EngineConfig::no_sound_mode);
}

} // namespace engine::audio

