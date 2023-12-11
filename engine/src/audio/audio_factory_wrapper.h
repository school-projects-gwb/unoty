
#ifndef ENGINE_SRC_AUDIO_SDL_AUDIO_AUDIO_FACTORY_WRAPPER_H
#define ENGINE_SRC_AUDIO_SDL_AUDIO_AUDIO_FACTORY_WRAPPER_H

#include <memory>

#include "audio_factory_base.h"
#include "engine/engine_config.h"

namespace engine::audio {
class AudioFactoryWrapper {
 public:
  AudioFactoryWrapper(const AudioFactoryWrapper &) = delete;
  AudioFactoryWrapper(AudioFactoryWrapper &&) = delete;
  AudioFactoryWrapper &operator=(const AudioFactoryWrapper &) = delete;
  AudioFactoryWrapper &operator=(AudioFactoryWrapper &&) = delete;

  void SetAudioFactory(std::unique_ptr<AudioFactoryBase> base);
  Audio *CreateAudio(const std::string &file_path);
  static AudioFactoryWrapper &GetInstance();

 private:
  std::unique_ptr<AudioFactoryBase> audio_factory_base_;
  AudioFactoryWrapper() = default;
  ~AudioFactoryWrapper() = default;
};
} // namespace engine::audio
#endif //ENGINE_SRC_AUDIO_SDL_AUDIO_AUDIO_FACTORY_WRAPPER_H
