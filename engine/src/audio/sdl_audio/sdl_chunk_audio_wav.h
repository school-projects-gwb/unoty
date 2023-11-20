#ifndef ENGINE_SRC_AUDIO_AUDIO_H_
#define ENGINE_SRC_AUDIO_AUDIO_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <utility>
#include "../audio.h"
#include "sdl_audio_manager.h"

namespace engine::audio {

class SdlChunkAudioWav : public Audio {

public:
    explicit SdlChunkAudioWav(std::string file_path) {
      path = std::move(file_path);
      volume_ = CALCULATE_VOLUME(volume_);

      track_number_ = engine::audio::SdlAudioManager::get_instance().LoadSound(path);
    }
    ~SdlChunkAudioWav() override {
      engine::audio::SdlAudioManager::get_instance().FreeSound(track_number_, channel_);
    }

  void Play() override;
  void Stop() override;

  void TogglePaused() override;
  bool IsPaused() override;

  void SetVolume(int volume) override;
  int GetVolume() override;
  void SetPitch(int pitch) override;
  int GetPitch() override;
  void SetSpeed(int speed) override;
  int GetSpeed() override;

 private:
  int track_number_ = -1;
  int channel_ = -1;
};
}

#endif //ENGINE_SRC_AUDIO_AUDIO_H_
