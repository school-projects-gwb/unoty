#include <utility>
#include <regex>
#include "unordered_map"
#include "level_loader_config.h"

#ifndef SLIME_SHOOTER_SRC_CONFIG_SLIME_SHOOTER_SRC_CONFIG_LEVEL_EDITOR_CONFIG_H_
#define SLIME_SHOOTER_SRC_CONFIG_SLIME_SHOOTER_SRC_CONFIG_LEVEL_EDITOR_CONFIG_H_

namespace slime_shooter {

///@brief Logic for Level Editor functionality such as saving and deleting
class LevelEditorConfig {
 public:
  static void SaveLevel(const std::unordered_map<std::string, std::string> &level_values) {
    is_edit_new_ ? SaveNewLevel(level_values) : SaveExistingLevel(level_values);
  }

  static void DeleteCurrentActiveLevel() {
    auto available_levels = LevelLoaderConfig::GetAvailableLevels();
    if (available_levels.size() == 1) return; // Cannot delete the only existing level

    try {
      auto level_path = LevelLoaderConfig::GetActiveLevelPath();
      std::filesystem::remove(level_path);

      // Set first available level that is not the deleted level as active.
      for (const auto& available_level : available_levels)
        if (available_level.second != level_path) {
          GameConfig::SetPropertyValue("active_level_path", available_level.second);
          break;
        }

      LevelLoaderConfig::ReloadLevelData();
    } catch (const std::filesystem::filesystem_error& e) {
      std::cerr << "Error deleting file: " << e.what() << "\n";
    }
  }

  static void EnableEditor(bool is_new_level) {
    is_edit_new_ = is_new_level;
  }

  /// @brief Used for determining whether existing or new level is being edited
  static bool IsNewLevel() {
    return is_edit_new_;
  }

 private:
  static bool is_edit_new_;

  static void SaveExistingLevel(const std::unordered_map<std::string, std::string> &level_values) {
    auto level_path = LevelLoaderConfig::GetActiveLevelPath();
    auto config_file_data = engine::data_handler::FileHandler::GetInstance().ReadFile(level_path);
    auto deserialized_config = engine::data_handler::Serializer::Deserialize(engine::data_handler::SerializerType::Json,
                                                                             config_file_data);

    for (auto data_pair : level_values)
      deserialized_config.SetValue(data_pair.first, data_pair.second);

    auto serialized_config = engine::data_handler::Serializer::Serialize(
        engine::data_handler::SerializerType::Json, deserialized_config);
    engine::data_handler::FileHandler::GetInstance().WriteFile(level_path, serialized_config);

    LevelLoaderConfig::ReloadLevelData();
  }

  static void SaveNewLevel(const std::unordered_map<std::string, std::string> &level_values) {
    auto existing_levels = LevelLoaderConfig::GetAvailableLevels();

    std::regex pattern("Level ([0-9]+)");

    int highest_number = 0;
    std::vector<int> existing_numbers;

    // Collects all current level names (by integer identifier in level filename)
    for (const auto &existing_level : existing_levels) {
      std::smatch matches;
      if (std::regex_search(existing_level.first, matches, pattern) && matches.size() > 1) {
        int level_number = std::stoi(matches[1]);
        existing_numbers.push_back(level_number);
        if (level_number > highest_number) highest_number = level_number;
      }
    }

    int new_level_number;

    // Try finding gap in sequence (i.e. if 1 and 3 exist but 2 has been deleted, next level will be 2)
    for (new_level_number = 1; new_level_number <= highest_number + 1; ++new_level_number)
      if (std::find(existing_numbers.begin(), existing_numbers.end(), new_level_number) == existing_numbers.end())
        break;

    engine::data_handler::DataObject new_level;

    new_level.SetValue("level_name", "Level " + std::to_string(new_level_number));
    for (const auto &level_value : level_values)
      new_level.SetValue(level_value.first, level_value.second);

    auto serialized_level = engine::data_handler::Serializer::Serialize(
        engine::data_handler::SerializerType::Json, new_level);

    auto level_directory_path = LevelLoaderConfig::GetLevelDirectoryPath();
    auto new_level_path = level_directory_path + "/" + "level_" + std::to_string(new_level_number) + ".json";
    engine::data_handler::FileHandler::GetInstance().WriteFile(new_level_path, serialized_level);

    GameConfig::SetPropertyValue("active_level_path", new_level_path);
    LevelLoaderConfig::ReloadLevelData();
  }
};

}
#endif //SLIME_SHOOTER_SRC_CONFIG_SLIME_SHOOTER_SRC_CONFIG_LEVEL_EDITOR_CONFIG_H_
