#ifndef ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_SOUND_EFFECT_WRAPPER_H
#define ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_SOUND_EFFECT_WRAPPER_H

#include <string>
#include <utility>
#include <stdexcept>

#include <SDL.h>
#include <SDL_mixer.h>

#include "../audio.h"
#include "sdl_mixer_adapter.h"

namespace engine::audio {
class SDLSoundEffectWrapper : public Audio {
 public:
  explicit SDLSoundEffectWrapper(std::string file_path);

  void Play() override;
  void Stop() override;

  void TogglePaused() override;
  bool IsPaused() override;

  void SetVolume(int volume) override;
  int GetVolume() override;
 private:
  std::string name_;
  int channel_ = -1;
};
} // namespace engine::audio

#endif //ENGINE_SRC_AUDIO_SDL_AUDIO_SDL_SOUND_EFFECT_WRAPPER_H
