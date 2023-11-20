
#ifndef ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_MUSIC_AUDIO_MP3_H
#define ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_MUSIC_AUDIO_MP3_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <utility>
#include "../audio.h"
#include "sdl_audio_manager.h"

namespace engine::audio {

class SdlMusicAudioMp3 : public Audio {
 public:
  explicit SdlMusicAudioMp3(std::string file_path) {
    path = std::move(file_path);
    volume_ = CALCULATE_VOLUME(volume_);

    track_number_ = engine::audio::SdlAudioManager::get_instance().LoadMusic(path);
  }
  ~SdlMusicAudioMp3() override {
    engine::audio::SdlAudioManager::get_instance().FreeMusic(track_number_);
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
};
}

#endif //ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_MUSIC_AUDIO_MP3_H
