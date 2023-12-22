#ifndef SLIME_SHOOTER_SRC_SCENES_SLIME_SHOOTER_SRC_SCENES_LEVEL_LOADER_H_
#define SLIME_SHOOTER_SRC_SCENES_SLIME_SHOOTER_SRC_SCENES_LEVEL_LOADER_H_

#include "string"
#include "data_handler/file_handler/file_handler.h"
#include "data_handler/serializer.h"
#include "game_config.h"
#include "filesystem"
#include "iostream"
#include <sstream>
#include <codecvt>
#include "entities/structs/point.h"

namespace slime_shooter {

class LevelLoaderConfig {
 public:
  static const std::string &GetPropertyValue(const std::string& property_name) {
    try {
      return level_data_.at(property_name);
    } catch (const std::out_of_range& e) {
      return empty_property_value_;
    }
  }

  /// @brief Assume string_value is in format "<number><comma><number>". For example: "49,123"
  static engine::entities::Vector2d GetPositionFromString(const std::string& string_value) {
    std::istringstream iss(string_value);

    int pos_x;
    iss >> pos_x;

    char separator;
    iss >> separator;

    int pos_y;
    iss >> pos_y;

    return {pos_x, pos_y};
  }

  static engine::entities::Vector2d GetEditorPositionFromString(const std::string& string_value) {
    auto world_position = GetPositionFromString(string_value);
    return {static_cast<float>(world_position.x/3), static_cast<float>(world_position.y/2.8)};
  }

  static engine::entities::Vector2d GetWorldPositionFromEditorPosition(const engine::entities::Vector2d &editor_position) {
    return {static_cast<float>(editor_position.x*3), static_cast<float>(editor_position.y*2.8)};
  }

  static std::string StringifyPosition(engine::entities::Vector2d target_position) {
    return std::to_string((int)round(target_position.x)) + "," + std::to_string((int)round(target_position.y));
  }

  static const std::map<std::string, std::string> &GetAvailableLevels() {
    return available_levels_;
  }

  static void ReloadLevelData() {
    active_level_path_ = GameConfig::GetPropertyValue("active_level_path");
    level_data_.clear();

    auto level_file_data = engine::data_handler::FileHandler::GetInstance().ReadFile(active_level_path_);
    auto deserialized_level = engine::data_handler::Serializer::Deserialize(
        engine::data_handler::SerializerType::Json,level_file_data);

    // Stringify all data; assume all data consists of a simple key-value pair
    for (auto value : deserialized_level.GetData())
      if (std::holds_alternative<std::string>(value.second))
        level_data_[value.first] = std::get<std::string>(value.second);

    InitAvailableLevels();
  }

  static const std::string &GetActiveLevelPath() {
    return active_level_path_;
  }

  static const std::string &GetLevelDirectoryPath() {
    return level_directory_path_;
  }

  static const std::string &EmptyValue() {
    return empty_property_value_;
  }
 private:
  const static std::string level_directory_path_;
  static std::string active_level_path_;
  static std::map<std::string, std::string> available_levels_;
  static std::unordered_map<std::string, std::string> level_data_;
  static std::string empty_property_value_;

  static void InitAvailableLevels() {
    try {
      available_levels_.clear();
      std::vector<std::filesystem::path> paths;

      // Collect all level paths in directory
      for (const auto& entry : std::filesystem::directory_iterator(level_directory_path_)) {
        if (!entry.is_regular_file()) continue;

        const auto& path = entry.path();
        paths.push_back(path);
      }

      // Makes sure level paths are sorted by name
      std::sort(paths.begin(), paths.end(), [](const auto& a, const auto& b) {
        return a.filename() < b.filename();
      });

      // Deserializes levels and populate available_levels_
      for (const auto& path : paths) {
        std::string path_string = path.generic_string();
        std::replace(path_string.begin(), path_string.end(), '\\', '/');

        auto level_file_data = engine::data_handler::FileHandler::GetInstance().ReadFile(path_string);
        auto deserialized_level = engine::data_handler::Serializer::Deserialize(
            engine::data_handler::SerializerType::Json, level_file_data);

        auto level_name = deserialized_level.GetValue("level_name");
        if (std::holds_alternative<std::string>(level_name))
          available_levels_[std::get<std::string>(level_name)] = path_string;
      }
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << "\n";
    }
  }
};

}

#endif //SLIME_SHOOTER_SRC_SCENES_SLIME_SHOOTER_SRC_SCENES_LEVEL_LOADER_H_
