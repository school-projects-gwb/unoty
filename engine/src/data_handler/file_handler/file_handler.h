#ifndef ENGINE_SRC_DATA_HANDLER_FILE_HANDLER_FILE_HANDLER_H_
#define ENGINE_SRC_DATA_HANDLER_FILE_HANDLER_FILE_HANDLER_H_

#include <string>
#include <iostream>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace engine::data_handler {

class FileHandler {
 public:
  json ReadFile(const std::string& file_path);
  void WriteFile(const std::string& file_path);
};

} // engine::data_handler

#endif // ENGINE_SRC_DATA_HANDLER_FILE_HANDLER_FILE_HANDLER_H_
