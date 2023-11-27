#ifndef ENGINE_SRC_ENGINE_ENGINE_TICK_H_
#define ENGINE_SRC_ENGINE_ENGINE_TICK_H_

#include <chrono>
#include <thread>

namespace engine {

class EngineTick {
 public:
  void Init(int target_fps);

  void StartFrame();
  void UpdateCurrentFrame();
  [[nodiscard]] bool ShouldIterate() const;
  void UpdateFps();

  void SetTargetFps(int new_frames_per_second);

  [[nodiscard]] int GetMostRecentFps() const;
 private:
  double fixed_time_step_;
  double current_time_;
  double elapsed_time_;
  double previous_time_ = GetCurrentTime();
  double fps_update_time_ = previous_time_;
  double delta_time_;
  int frame_counter_;
  int most_recent_fps_;
  double fps_update_interval_ = 1.0;

  [[nodiscard]] double GetCurrentTime() const;
  std::chrono::time_point<std::chrono::high_resolution_clock> frame_start_time_;
};

}

#endif //ENGINE_SRC_ENGINE_ENGINE_TICK_H_
