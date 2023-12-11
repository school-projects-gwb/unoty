#ifndef ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_MUSIC_WRAPPER_H
#define ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_MUSIC_WRAPPER_H

#include <string>
#include <utility>
#include <stdexcept>

#include <SDL.h>
#include <SDL_mixer.h>

#include "../audio.h"
#include "sdl_mixer_adapter.h"

namespace engine::audio {
class SDLMusicWrapper : public Audio {
 public:
  explicit SDLMusicWrapper(std::string file_path);

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
  ~SDLMusicWrapper() override;
};
} // namespace engine::audio

#endif //ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_MUSIC_WRAPPER_H
