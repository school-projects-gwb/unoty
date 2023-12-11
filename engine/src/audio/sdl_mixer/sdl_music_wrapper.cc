#include "sdl_music_wrapper.h"

namespace engine::audio {

SDLMusicWrapper::SDLMusicWrapper(std::string file_path) {
  file_path_ = std::move(file_path);
  volume_ = CALCULATE_VOLUME(volume_);
  track_number_ = SDLMixerAdapter::GetInstance().EnqueueMusic(file_path_);
}

SDLMusicWrapper::~SDLMusicWrapper() {
  SDLMixerAdapter::GetInstance().FreeMusic(track_number_);
}

void SDLMusicWrapper::Play() {
  SDLMixerAdapter::GetInstance().PlayMusic(track_number_, volume_, static_cast<int>((!loop_) - 1));
}

void SDLMusicWrapper::Stop() {
  SDLMixerAdapter::GetInstance().StopMusic(track_number_);
}

void SDLMusicWrapper::TogglePaused() {
  paused_ = SDLMixerAdapter::GetInstance().PauseMusic(track_number_);
}

bool SDLMusicWrapper::IsPaused() {
  return paused_;
}

void SDLMusicWrapper::SetVolume(int volume) {
  volume_ = SDLMixerAdapter::GetInstance().ChangeMusicVolume(track_number_, volume);
}

int SDLMusicWrapper::GetVolume() {
  return volume_;
}

void SDLMusicWrapper::SetPitch(int pitch) {
  pitch_ = pitch;
}

int SDLMusicWrapper::GetPitch() {
  return pitch_;
}

void SDLMusicWrapper::SetSpeed(int speed) {
  speed_ = speed;
}

int SDLMusicWrapper::GetSpeed() {
  return speed_;
}

} // namespace engine::audio
