#ifndef ENGINE_SRC_AUDIO_AUDIO_H_
#define ENGINE_SRC_AUDIO_AUDIO_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "audio.h"
#include <iostream>
#include <string>
#include <utility>

namespace engine::audio {

class SdlAudio : public Audio {

public:
    explicit SdlAudio(std::string filePath) {
      path = std::move(filePath);
    }
    void * Start(bool looping) override;
    void Stop() override;
};
}

#endif //ENGINE_SRC_AUDIO_AUDIO_H_
