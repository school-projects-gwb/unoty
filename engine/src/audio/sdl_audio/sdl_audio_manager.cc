
#include "sdl_audio_manager.h"

namespace engine::audio {
SdlAudioManager SdlAudioManager::instance_;

int SdlAudioManager::LoadMusic(const std::string &filename) {
  Mix_Music *m = Mix_LoadMUS(filename.c_str());

  if(m == nullptr) {
    printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
    return -1;
  }

  music_.push_back(m);
  return (int)music_.size()-1;
}
std::string SdlAudioManager::LoadSound(const std::string &filename) {
  Mix_Chunk *s = Mix_LoadWAV(filename.c_str());
  std::string base_filename = filename.substr(filename.find_last_of("/\\") + 1);

  if(s == nullptr) {
    printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
    return "";
  }

  if (sounds_[base_filename].first != nullptr) {
    sounds_[base_filename].second++;
  } else {
    sounds_[base_filename] = {s, 1};
  }

  return base_filename;
}

int SdlAudioManager::PlayMusic(int m, int volume, int loops) {
  if(Mix_PlayingMusic() != 0) {
    Mix_HaltMusic();
  }

  Mix_VolumeMusic(volume);
  if (Mix_PlayMusic(music_[m], loops) == 0){
    current_music_ = m;
  }

  return 0;
}
int SdlAudioManager::PlaySound(const std::string& s, int volume, int loops) {
  int channel = Mix_PlayChannel(-1, sounds_[s].first, loops);
  if (channel != -1) {
    Mix_Volume(channel, volume);
  }
  return channel;
}

void SdlAudioManager::StopMusic(int m) const {
  if(current_music_ == m) {
    Mix_HaltMusic();
  }
}
void SdlAudioManager::StopSound(const std::string& s, int channel) {
  auto ch = Mix_GetChunk(channel);
  if (ch != nullptr && *sounds_[s].first->abuf == *ch->abuf) {
    Mix_HaltChannel(channel);
  }
}

bool SdlAudioManager::PauseMusic(int m) const {
  if(current_music_ != m) {
    return false;
  }

  if(Mix_PausedMusic() == 1) {
    Mix_ResumeMusic();
    return false;
  } else {
    Mix_PauseMusic();
    return true;
  }
}
bool SdlAudioManager::PauseSound(const std::string& s, int channel) {
  auto ch = Mix_GetChunk(channel);
  if (ch == nullptr || *sounds_[s].first->abuf != *ch->abuf) {
    return false;
  }

  if(Mix_Paused(channel) == 1) {
    Mix_Resume(channel);
    return false;
  } else {
    Mix_Pause(channel);
    return true;
  }
}

void SdlAudioManager::FreeMusic(int m) {
  if(current_music_ == m) {
    Mix_HaltMusic();
  }
  Mix_FreeMusic(music_[m]);
  music_[m] = nullptr;
}
void SdlAudioManager::FreeSound(const std::string& s, int channel) {
  sounds_[s].second--;
  if (sounds_[s].second == 0){
    Mix_HaltChannel(channel);
    Mix_FreeChunk(sounds_[s].first);
    sounds_[s] = {nullptr, 0};
  }
}
}