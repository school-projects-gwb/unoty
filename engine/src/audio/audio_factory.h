
#ifndef ENGINE_SRC_AUDIO_AUDIO_FACTORY_H
#define ENGINE_SRC_AUDIO_AUDIO_FACTORY_H

#include "audio.h"
#include "sdl_audio/sdl_chunk_audio_wav.h"
#include "sdl_audio/sdl_music_audio_mp3.h"
#include "audio_factory_base.h"
#include <string>
#include <filesystem>

namespace engine::audio {
class AudioFactory : public AudioFactoryBase {
 public:
  ~AudioFactory() override = default;
  Audio* CreateAudio(const std::string& file_path) override;
};
}

#endif //ENGINE_SRC_AUDIO_AUDIO_FACTORY_H
