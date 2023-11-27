#include <iostream>
#include "engine_tick.h"
#include "utility/debug.h"

namespace engine {
  void EngineTick::Init(int target_fps) {
    SetTargetFps(target_fps);
    current_time_ = GetCurrentTime();
  }

  double EngineTick::GetCurrentTime() const {
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<double>;

    auto current_time = Clock::now();
    auto duration = std::chrono::duration_cast<Duration>(current_time.time_since_epoch());

    return duration.count();
  }

  int EngineTick::GetMostRecentFps() const {
    return most_recent_fps_;
  }

  void EngineTick::StartFrame() {
    current_time_ = GetCurrentTime();
    delta_time_ = current_time_ - previous_time_;
    previous_time_ = current_time_;

    elapsed_time_ += delta_time_;
  }

  bool EngineTick::ShouldIterate() const {
    return elapsed_time_ >= fixed_time_step_;
  }

  void EngineTick::UpdateCurrentFrame() {
    frame_counter_++;
    elapsed_time_ -= fixed_time_step_;
  }

  void EngineTick::UpdateFps() {
    if (current_time_ - fps_update_time_ >= fps_update_interval_) {
      most_recent_fps_ = frame_counter_;
      frame_counter_ = 0;
      fps_update_time_ = current_time_;
    }
  }

  void EngineTick::SetTargetFps(int new_frames_per_second) {
    fixed_time_step_ = 1.0 / new_frames_per_second;
  }
}