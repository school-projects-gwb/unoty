#include <iostream>
#include "engine_tick.h"
#include "helpers/debug.h"

namespace engine {
  void EngineTick::Init(int target_fps) {
    fixed_time_step_ = 1.0 / (target_fps + 0.0);
    accumulator_ = 0.0;
    current_time_ = GetCurrentTime();
    frame_start_time_ = std::chrono::high_resolution_clock::now();
  }

  double EngineTick::GetDeltaTime() {
    double new_time = GetCurrentTime();
    double frame_time = new_time - current_time_;
    current_time_ = new_time;
    return frame_time;
  }

double EngineTick::GetCurrentTime() const {
  using Clock = std::chrono::high_resolution_clock;
  using Duration = std::chrono::duration<double>;

  auto current_time = Clock::now();
  auto duration = std::chrono::duration_cast<Duration>(current_time.time_since_epoch());

  return duration.count();
}

  double EngineTick::GetAccumulator() const {
    return accumulator_;
  }

  void EngineTick::AppendAccumulator(double value) {
    accumulator_ += value;
  }

  void EngineTick::SubtractAccumulator(double value) {
    accumulator_ -= value;
  }

  double EngineTick::GetFixedTimeStep() const {
    return fixed_time_step_;
  }

  void EngineTick::IncreaseFrameCounter() {
    frame_counter_++;
  }

  void EngineTick::IncreaseElapsed() {
    elapsed_time_ += GetDeltaTime();
  }

  void EngineTick::ShowFps(const std::string& title) {
    if (elapsed_time_ < 1.0) return;
    helpers::Debug::Log(title + " FPS: " + std::to_string(frame_counter_));
    frame_counter_ = 0;
    elapsed_time_ = 0.0;
  }
}