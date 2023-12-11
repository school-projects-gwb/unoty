#ifndef ENGINE_SRC_AUDIO_AUDIO_FACTORY_H
#define ENGINE_SRC_AUDIO_AUDIO_FACTORY_H

#include <string>
#include <filesystem>

#include "audio.h"
#include "null_audio.h"
#include "audio_factory_base.h"
#include "sdl_mixer/sdl_music_wrapper.h"
#include "sdl_mixer/sdl_sound_effect_wrapper.h"

namespace engine::audio {
class AudioFactory : public AudioFactoryBase {
 public:
  ~AudioFactory() override = default;
  Audio *CreateAudio(const std::string &file_path, bool no_sound_mode) override;
};
} // namespace engine::audio

#endif //ENGINE_SRC_AUDIO_AUDIO_FACTORY_H
