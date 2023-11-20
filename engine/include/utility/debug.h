#ifndef ENGINE_INCLUDE_HELPERS_ENGINE_INCLUDE_HELPERS_DEBUG_H_
#define ENGINE_INCLUDE_HELPERS_ENGINE_INCLUDE_HELPERS_DEBUG_H_

#include <iostream>

namespace engine::helpers {

/// @brief Used to log messages and errors in the standard output
class Debug {
public:
  /// @brief Logs regular debug message to standard output
  static void Log(const std::string& message) {
    std::string ascii_yellow = "\x1b[33m";
    std::cout << ascii_yellow << "[DEBUG]  " << GetAsciiResetColor() << message << "\n";
  }

  /// @brief Logs error message to standard output
  static void Error(const std::string& message) {
    std::cerr << "[ERROR]  " << message << "\n";
  }

  /// @overload
  static void Log(int value) {
    Log(std::to_string(value));
  }

  /// @overload
  static void Log(float value) {
    Log(std::to_string(value));
  }

  /// @overload
  static void Error(int value) {
    Error(std::to_string(value));
  }

  /// @overload
  static void Error(float value) {
    Error(std::to_string(value));
  }
 private:
  static std::string GetAsciiResetColor() {
    return "\x1b[0m";
  }
};

}

#endif //ENGINE_INCLUDE_HELPERS_ENGINE_INCLUDE_HELPERS_DEBUG_H_
