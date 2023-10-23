#ifndef ENGINE_SRC_ENGINE_ENGINE_TICK_H_
#define ENGINE_SRC_ENGINE_ENGINE_TICK_H_

#include <chrono>
#include <thread>

namespace engine {

class EngineTick {
 public:
  void Init(int target_fps);

  double GetDeltaTime();
  [[nodiscard]] double GetCurrentTime() const;
  [[nodiscard]] double GetFixedTimeStep() const;
  [[nodiscard]] double GetAccumulator() const;

  void AppendAccumulator(double value);
  void SubtractAccumulator(double value);

  void IncreaseFrameCounter();
  void IncreaseElapsed();
  void ShowFps(const std::string& title);
 private:
  double fixed_time_step_;
  double accumulator_;
  double current_time_;
  int frame_counter_;
  double elapsed_time_;
  std::chrono::time_point<std::chrono::high_resolution_clock> frame_start_time_;
};

}

#endif //ENGINE_SRC_ENGINE_ENGINE_TICK_H_
