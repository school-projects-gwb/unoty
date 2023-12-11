#ifndef ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_TIMER_H_
#define ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_TIMER_H_

#include <chrono>

namespace engine::utility {

/// @brief Basic timer that allows for keeping track of elapsed time
class Timer {
 public:
  Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

  /// @brief Starts timer, also used to Restart it
  void Start() {
    is_running_ = true;
    start_time_ = std::chrono::high_resolution_clock::now();
  }

  void Stop() {
    is_running_ = false;
  }

  [[nodiscard]] double GetElapsedSeconds() const {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_);
    return duration.count() / 1e6; // Convert microseconds to seconds
  }

  [[nodiscard]] bool HasElapsed(double seconds) const {
    return GetElapsedSeconds() >= seconds;
  }

  [[nodiscard]] bool IsRunning() const {
    return is_running_;
  }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
  bool is_running_ = false;
};

}

#endif //ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_TIMER_H_
