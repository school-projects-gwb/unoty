
#ifndef ENGINE_SRC_AUDIO_AUDIO_H
#define ENGINE_SRC_AUDIO_AUDIO_H

#include <string>
class Audio {
 public:
  std::string path;
  bool loop_ = false;

  virtual void Play() = 0;
  virtual void Stop() = 0;

  virtual void TogglePaused() = 0;
  virtual bool IsPaused() = 0 ;

  virtual void SetVolume(int volume) = 0;
  virtual int GetVolume() = 0;
  virtual void SetPitch(int pitch) = 0;
  virtual int GetPitch() = 0;
  virtual void SetSpeed(int speed) = 0;
  virtual int GetSpeed() = 0;

  virtual ~Audio() = default;

 protected:
  // 100 for %
  int volume_ = 100;
  int pitch_ = 100;
  int speed_ = 100;

  bool paused_ = false;
};

#endif //ENGINE_SRC_AUDIO_AUDIO_H
