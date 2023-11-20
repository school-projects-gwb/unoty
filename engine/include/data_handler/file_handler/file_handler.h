#ifndef ENGINE_DATA_HANDLER_FILE_HANDLER_FILE_HANDLER_H
#define ENGINE_DATA_HANDLER_FILE_HANDLER_FILE_HANDLER_H

#include <string>
#include <memory>

namespace engine::data_handler {

/// @brief Handles interactions between the filesystem and the application.
class FileHandler {
 public:
  ~FileHandler();

  /// @brief Returns a singleton instance so that it can be easily accessed at various points in the application.
  static FileHandler& GetInstance();

  /// @brief Reads the file at the given location and attempts to parse it to a json object.
  std::string ReadFile(const std::string &path);

  /// @brief Attempts to write the given json object to a file at the given location.
  void WriteFile(const std::string &path, const std::string &s);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;

  FileHandler();
};
} // namespace engine::data_handler

#endif // ENGINE_DATA_HANDLER_FILE_HANDLER_FILE_HANDLER_H
