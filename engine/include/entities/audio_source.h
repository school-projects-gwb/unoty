#ifndef ENGINE_INCLUDE_ENTITIES_AUDIO_SOURCE_H_
#define ENGINE_INCLUDE_ENTITIES_AUDIO_SOURCE_H_

#include "component.h"

namespace engine::entities {

/// @brief Contains logic to play audio
class AudioSource : public Component {
 public:
  explicit AudioSource(const std::string& track);
  ~AudioSource() override;
  void Play();
  void Stop();

  void TogglePaused();
  bool IsPaused();
  void ToggleLooping();
  bool IsLooping();

  void SetVolume(int volume);
  int GetVolume();

  bool play_on_wake_ = false;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_AUDIO_SOURCE_H_
