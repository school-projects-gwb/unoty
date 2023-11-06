
#ifndef ENGINE_SRC_AUDIO_AUDIO_H
#define ENGINE_SRC_AUDIO_AUDIO_H

#include <string>
class Audio {
 public:
  std::string path;
  bool PlayOnWake = false;
  bool loop = false;
  //volume

  virtual void* Start(bool looping) = 0;
  virtual void Stop() = 0;

  virtual ~Audio() = default;
};

#endif //ENGINE_SRC_AUDIO_AUDIO_H
