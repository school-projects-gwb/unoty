#include "sdl_sound_effect_wrapper.h"

namespace engine::audio {

SDLSoundEffectWrapper::SDLSoundEffectWrapper(std::string file_path) {
  file_path_ = std::move(file_path);
  volume_ = CALCULATE_VOLUME(volume_);
  name_ = SDLMixerAdapter::GetInstance()->AddSound(file_path_);
}

void SDLSoundEffectWrapper::Play() {
  channel_ = SDLMixerAdapter::GetInstance()->PlaySound(name_, static_cast<int>((!loop_) - 1));
}

void SDLSoundEffectWrapper::Stop() {
  SDLMixerAdapter::GetInstance()->StopSound(name_, channel_);
}

void SDLSoundEffectWrapper::TogglePaused() {
  paused_ = SDLMixerAdapter::GetInstance()->PauseSound(name_, channel_);
}

bool SDLSoundEffectWrapper::IsPaused() {
  return paused_;
}

void SDLSoundEffectWrapper::SetVolume(int volume) {
  volume_ = SDLMixerAdapter::GetInstance()->ChangeSoundVolume(name_, volume);
}

int SDLSoundEffectWrapper::GetVolume() {
  return volume_;
}

} // namespace engine::audio