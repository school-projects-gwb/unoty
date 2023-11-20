#ifndef ENGINE_INCLUDE_HELPERS_PATH_HELPER_H
#define ENGINE_INCLUDE_HELPERS_PATH_HELPER_H

#include <string>
#include <filesystem>

namespace engine::helpers {

/// @brief Helper for paths
class PathHelper {
  public:
    /// @brief Assume working directory (current_path) is directory where executable is located
    static const std::string GetFullPathFromRelative(const std::string& relative_path) {
      std::filesystem::path current_path = std::filesystem::current_path();
      std::string full_path = current_path.string() + "/" + relative_path;

      return full_path;
    }
};

}

#endif //ENGINE_INCLUDE_HELPERS_PATH_HELPER_H
