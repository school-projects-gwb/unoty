
#ifndef ENGINE_SRC_AUDIO_SDL_AUDIO_AUDIO_FACTORY_WRAPPER_H
#define ENGINE_SRC_AUDIO_SDL_AUDIO_AUDIO_FACTORY_WRAPPER_H

#include <memory>
#include "audio_factory_base.h"

namespace engine::audio {
class AudioFactoryWrapper {
 public:
  static AudioFactoryWrapper& get_instance() { return instance_; }

  // prohibit copy & move
  AudioFactoryWrapper(const AudioFactoryWrapper&) = delete;
  AudioFactoryWrapper(AudioFactoryWrapper&&) = delete;
  AudioFactoryWrapper& operator=(const AudioFactoryWrapper&) = delete;
  AudioFactoryWrapper& operator=(AudioFactoryWrapper&&) = delete;

  void SetAudioFactory(std::unique_ptr<AudioFactoryBase> base) {
    audio_factory_base_ = std::move(base);
  }

  Audio *CreateAudio(const std::string& file_path) {
    return audio_factory_base_->CreateAudio(file_path);
  }
 private:
  std::unique_ptr<AudioFactoryBase> audio_factory_base_;
  static AudioFactoryWrapper instance_;

  AudioFactoryWrapper() = default;
  ~AudioFactoryWrapper() = default;
};
}
#endif //ENGINE_SRC_AUDIO_SDL_AUDIO_AUDIO_FACTORY_WRAPPER_H
