#ifndef ENGINE_SRC_AUDIO_NULL_AUDIO_H
#define ENGINE_SRC_AUDIO_NULL_AUDIO_H

#include <string>

#include "audio.h"

namespace engine::audio {
class NullAudio : public Audio {
 public:
  explicit NullAudio(std::string file_path) {
    file_path_ = std::move(file_path);
    volume_ = 0;
  }

  void Play() override {};
  void Stop() override {};

  void TogglePaused() override { paused_ = !paused_; };
  bool IsPaused() override { return paused_; };

  void SetVolume(int volume) override { volume_ = volume; };
  int GetVolume() override { return volume_; };
};
} // namespace engine::audio

#endif //ENGINE_SRC_AUDIO_NULL_AUDIO_H
