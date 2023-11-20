
#include "sdl_music_audio_mp3.h"

namespace engine::audio {

void SdlMusicAudioMp3::Play() {
  SdlAudioManager::get_instance().PlayMusic(track_number_, volume_, (int)((!loop_) - 1));
}
void SdlMusicAudioMp3::Stop() {
  SdlAudioManager::get_instance().StopMusic(track_number_);
}

void SdlMusicAudioMp3::TogglePaused() {
  paused_ = SdlAudioManager::get_instance().PauseMusic(track_number_);;
}
bool SdlMusicAudioMp3::IsPaused() {
  return paused_;
}

void SdlMusicAudioMp3::SetVolume(int volume) { volume_ = CALCULATE_VOLUME(volume); }
int SdlMusicAudioMp3::GetVolume() { return volume_; }

void SdlMusicAudioMp3::SetPitch(int pitch) { pitch_ = pitch; }
int SdlMusicAudioMp3::GetPitch() { return pitch_; }

void SdlMusicAudioMp3::SetSpeed(int speed) { speed_ = speed; }
int SdlMusicAudioMp3::GetSpeed() { return speed_; }

}
