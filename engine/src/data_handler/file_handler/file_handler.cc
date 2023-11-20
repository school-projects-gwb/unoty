#include "data_handler/file_handler/file_handler.h"

#include <stdexcept>
#include <string>
#include <fstream>
#include <ios>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace engine::data_handler {

class FileHandler::Impl {
 public:
  static void WriteFile(const std::string &path, const std::string &s) {
    if (path.substr(path.find_last_of('.') + 1) != "json")
      throw std::invalid_argument("[FileHandler.WriteFile]: Can't write a non-json file.");

    if (s.empty())
      throw std::invalid_argument("[FileHandler.Writefile]: File input is empty.");

    std::ofstream stream;
    stream.open(path);
    stream << s;
    stream.close();
  }

  static std::string ReadFile(const std::string &path) {

    if (path.substr(path.find_last_of('.') + 1) != "json")
      throw std::invalid_argument("[FileHandler.ReadFile]: Can't read a non-json file.");

    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path);

    if (not stream)
      throw std::ios_base::failure("[FileHandler.ReadFile]: File does not exist.");

    auto out = std::string();
    auto buf = std::string(read_size, '\0');

    while (stream.read(&buf[0], read_size)) {
      out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
  }

};

FileHandler::FileHandler() : impl_(std::make_unique<Impl>()) {}
FileHandler::~FileHandler() = default;

FileHandler &FileHandler::GetInstance() {
  static FileHandler instance;
  return instance;
}

void FileHandler::WriteFile(const std::string &path, const std::string &s) {
  impl_->WriteFile(path, s);
}

std::string FileHandler::ReadFile(const std::string &path) {
  return impl_->ReadFile(path);
}

} // namespace engine::data_handler