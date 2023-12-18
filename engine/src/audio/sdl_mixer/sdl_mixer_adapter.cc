#include "sdl_mixer_adapter.h"

namespace engine::audio {

class SDLMixerAdapter::Impl {
 public:
  int EnqueueMusic(const std::string &file_path) {
    auto m = Mix_LoadMUS(file_path.c_str());
    if (m == nullptr) {
      throw std::invalid_argument(file_path);
    }
    music_.emplace_back(m);
    return static_cast<int>(music_.size() - 1);
  }

  void PlayMusic(int index, int volume, int loops) {
    if (Mix_PlayingMusic()) {
      Mix_HaltMusic();
    }

    auto m = music_[index];
    if (Mix_PlayMusic(m, loops) == 0) {
      Mix_VolumeMusic(volume);
      current_music_ = index;
    }
  }

  void StopMusic(int track_number) const {
    if (current_music_ == track_number) {
      Mix_HaltMusic();
    }
  }

  [[nodiscard]] bool PauseMusic(int track_number) const {
    if (current_music_ == track_number) {
      if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
        return false;
      } else {
        Mix_PauseMusic();
        return true;
      }
    }
    return -1;
  }

  [[nodiscard]] int ChangeMusicVolume(int track_number, int volume) const {
    if (track_number != current_music_) return volume;

    int v = static_cast<int>(CALCULATE_VOLUME(volume));
    Mix_VolumeMusic(v);

    return v;
  }

  std::string AddSound(const std::string &file_path) {
    auto s = Mix_LoadWAV(file_path.c_str());
    std::string base = file_path.substr(file_path.find_last_of("/\\") + 1);

    if (s == nullptr) {
      throw std::invalid_argument(file_path);
    }

    if (sounds_[base].first != nullptr) {
      sounds_[base].second++;
    } else {
      sounds_[base] = {s, 1};
    }

    return base;
  }

  int PlaySound(const std::string &s, int loops) {
    int channel = Mix_PlayChannel(-1, sounds_.at(s).first, loops);
    return channel;
  }

  void StopSound(const std::string &s, int channel) {
    auto ch = Mix_GetChunk(channel);
    if (ch != nullptr && *sounds_[s].first->abuf == *ch->abuf) {
      Mix_HaltChannel(channel);
    }
  }

  bool PauseSound(const std::string &s, int channel) {
    auto ch = Mix_GetChunk(channel);
    if (sounds_[s].first == nullptr || *sounds_[s].first->abuf != *ch->abuf) return true;

    if (Mix_Paused(channel) == 1) {
      Mix_Resume(channel);
      return false;
    } else {
      Mix_Pause(channel);
      return true;
    }
  }

  int ChangeSoundVolume(const std::string &s, int volume) {
    auto c = sounds_[s].first;
    auto v = static_cast<int>(CALCULATE_VOLUME(volume));

    if (c == nullptr) throw std::invalid_argument(s);
    Mix_VolumeChunk(c, v);

    return v;
  }

  void FreeChunk(const std::string &s) {
    if (!sounds_.count(s)) return;
    sounds_[s].second--;

    if (sounds_[s].second <= 0) {
      Mix_FreeChunk(sounds_[s].first);
      sounds_[s].first = nullptr;
      sounds_.erase(s);
    }
  }

  void FreeMusic(int m) {
    auto c = music_[m];
    if (c == nullptr) return;
    Mix_FreeMusic(c);
    music_[m] = nullptr;
  }

  void CleanUp() {
    for (const auto &sound : sounds_)
      Mix_FreeChunk(sound.second.first);

    sounds_.clear();

    for (const auto &music : music_)
      Mix_FreeMusic(music);

    music_.clear();

    Mix_Quit();
  }

 private:
  std::vector<Mix_Music *> music_;
  std::map<std::string, std::pair<Mix_Chunk *, int>> sounds_;

  int current_music_ = -1;
};

SDLMixerAdapter::SDLMixerAdapter() : impl_(std::make_unique<Impl>()) {
  Mix_Init(MIX_INIT_OGG);
  SDL_Init(SDL_INIT_AUDIO);

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 2048) < 0) {
    printf("SDL_Mixer couldn't init. Err: %s\n", Mix_GetError());
  }
}

void SDLMixerAdapter::CleanUp() {
  impl_->CleanUp();
}

SDLMixerAdapter *SDLMixerAdapter::GetInstance() {
  static SDLMixerAdapter instance;
  return &instance;
}

int SDLMixerAdapter::EnqueueMusic(const std::string &file_path) {
  return impl_->EnqueueMusic(file_path);
}

void SDLMixerAdapter::PlayMusic(int index, int volume, int loops) {
  impl_->PlayMusic(index, volume, loops);
}

void SDLMixerAdapter::StopMusic(int track_number) {
  impl_->StopMusic(track_number);
}

bool SDLMixerAdapter::PauseMusic(int track_number) {
  return impl_->PauseMusic(track_number);
}

int SDLMixerAdapter::ChangeMusicVolume(int track_number, int volume) {
  return impl_->ChangeMusicVolume(track_number, volume);
}

std::string SDLMixerAdapter::AddSound(const std::string &file_path) {
  return impl_->AddSound(file_path);
}

int SDLMixerAdapter::PlaySound(const std::string &s, int loops) {
  return impl_->PlaySound(s, loops);
}

void SDLMixerAdapter::StopSound(const std::string &s, int channel) {
  impl_->StopSound(s, channel);
}

bool SDLMixerAdapter::PauseSound(const std::string &s, int channel) {
  return impl_->PauseSound(s, channel);
}

int SDLMixerAdapter::ChangeSoundVolume(const std::string &s, int volume) {
  return impl_->ChangeSoundVolume(s, volume);
}

void SDLMixerAdapter::FreeChunk(const std::string &s) {
  impl_->FreeChunk(s);
}

void SDLMixerAdapter::FreeMusic(int m) {
  impl_->FreeMusic(m);
}

} // namespace engine::audio