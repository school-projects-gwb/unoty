
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
int SdlAudioManager::LoadSound(const std::string &filename) {
  Mix_Chunk *s = Mix_LoadWAV(filename.c_str());

  if(s == nullptr) {
    printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
    return -1;
  }

  for (int i = 0; i < (int)sounds_.size(); i++) {
    if (sounds_[i].first != nullptr && *sounds_[i].first->abuf == *s->abuf) {
      sounds_[i].second++;
      return i;
    }
  }

  sounds_.emplace_back(s, 1);
  return (int)sounds_.size()-1;
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
int SdlAudioManager::PlaySound(int s, int volume, int loops) {
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
void SdlAudioManager::StopSound(int s, int channel) {
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
bool SdlAudioManager::PauseSound(int s, int channel) {
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
void SdlAudioManager::FreeSound(int s, int channel) {
  sounds_[s].second--;
  if (sounds_[s].second == 0){
    Mix_HaltChannel(channel);
    Mix_FreeChunk(sounds_[s].first);
    sounds_[s] = {nullptr, 0};
  }
}
}