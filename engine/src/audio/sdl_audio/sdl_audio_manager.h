
#ifndef ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_AUDIO_MANAGER_H
#define ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_AUDIO_MANAGER_H
#define CALCULATE_VOLUME(v) ((MIX_MAX_VOLUME * v) / 100)

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>

namespace engine::audio {

class SdlAudioManager {
 public:
  static SdlAudioManager& get_instance() { return instance_; }

  // prohibit copy & move
  SdlAudioManager(const SdlAudioManager&) = delete;
  SdlAudioManager(SdlAudioManager&&) = delete;
  SdlAudioManager& operator=(const SdlAudioManager&) = delete;
  SdlAudioManager& operator=(SdlAudioManager&&) = delete;

  int LoadMusic(const std::string& filename);
  int LoadSound(const std::string &filename);
  int PlayMusic(int m, int volume, int loops);
  int PlaySound(int s, int volume, int loops);
  void StopMusic(int m) const;
  void StopSound(int s, int channel);
  [[nodiscard]] bool PauseMusic(int m) const;
  bool PauseSound(int s, int channel);
  void FreeMusic(int m);
  void FreeSound(int s, int channel);


  static void Cleanup(){
    Mix_Quit();
  }
 private:
  std::vector<Mix_Music*> music_;
  std::vector<std::pair<Mix_Chunk*, int>> sounds_;
  int current_music_ = -1;

  static SdlAudioManager instance_;

  SdlAudioManager(){
      Mix_Init(MIX_INIT_MP3);
      SDL_Init(SDL_INIT_AUDIO);

      if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer couldn't init. Err: %s\n", Mix_GetError());
      }
  };
};

}

#endif //ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_AUDIO_MANAGER_H
