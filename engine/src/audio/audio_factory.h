
#ifndef ENGINE_SRC_AUDIO_AUDIO_FACTORY_H
#define ENGINE_SRC_AUDIO_AUDIO_FACTORY_H

#include "audio.h"
#include "sdl2_audio.h"
#include <string>

namespace engine::audio {
// CREATE AS SINGLETON
class audio_factory {

  Audio* CreateAudio(const std::string& filePath);
};
}

#endif //ENGINE_SRC_AUDIO_AUDIO_FACTORY_H
