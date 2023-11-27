#include "../level_loader_config.h"

namespace slime_shooter {

const std::string slime_shooter::LevelLoaderConfig::level_directory_path_ = "resources/levels";
std::string slime_shooter::LevelLoaderConfig::active_level_path_ = "resources/levels/level_1.json";
std::map<std::string, std::string> slime_shooter::LevelLoaderConfig::available_levels_;
std::unordered_map<std::string, std::string> slime_shooter::LevelLoaderConfig::level_data_;
std::string slime_shooter::LevelLoaderConfig::empty_property_value_;

}