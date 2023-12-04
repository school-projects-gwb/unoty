#include "sdl_chunk_audio_wav.h"


namespace engine::audio {

void SdlChunkAudioWav::Play() {
  channel_ = SdlAudioManager::get_instance().PlaySound(track_, volume_, (int)((!loop_) - 1));
}
void SdlChunkAudioWav::Stop() {
  SdlAudioManager::get_instance().StopSound(track_, channel_);
}

void SdlChunkAudioWav::TogglePaused() {
  paused_ = SdlAudioManager::get_instance().PauseSound(track_, channel_);
}
bool SdlChunkAudioWav::IsPaused() {
  return paused_;
}

void SdlChunkAudioWav::SetVolume(int volume) { volume_ = CALCULATE_VOLUME(volume); }
int SdlChunkAudioWav::GetVolume() { return volume_; }

void SdlChunkAudioWav::SetPitch(int pitch) { pitch_ = pitch; }
int SdlChunkAudioWav::GetPitch() { return pitch_; }

void SdlChunkAudioWav::SetSpeed(int speed) { speed_ = speed; }
int SdlChunkAudioWav::GetSpeed() { return speed_; }

}