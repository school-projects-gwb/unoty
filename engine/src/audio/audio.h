#ifndef ENGINE_SRC_AUDIO_AUDIO_H
#define ENGINE_SRC_AUDIO_AUDIO_H

#include <string>

class Audio {
 public:
  std::string file_path_;
  bool loop_ = false;

  virtual void Play() = 0;
  virtual void Stop() = 0;

  virtual void TogglePaused() = 0;
  virtual bool IsPaused() = 0;

  virtual void SetVolume(int volume) = 0;
  virtual int GetVolume() = 0;

  virtual ~Audio() = default;

 protected:
  int volume_ = 100;
  bool paused_ = false;
};

#endif //ENGINE_SRC_AUDIO_AUDIO_H
