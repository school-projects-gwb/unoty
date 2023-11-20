
#ifndef ENGINE_SRC_AUDIO_AUDIO_FACTORY_BASE_H
#define ENGINE_SRC_AUDIO_AUDIO_FACTORY_BASE_H

#include "audio.h"
namespace engine::audio {
class AudioFactoryBase {
 public:
  virtual ~AudioFactoryBase() = default;
  virtual Audio *CreateAudio(const std::string& file_path) = 0;
};
}
#endif //ENGINE_SRC_AUDIO_AUDIO_FACTORY_BASE_H
