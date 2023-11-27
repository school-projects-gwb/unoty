#include "../game_config.h"

namespace slime_shooter {

std::string slime_shooter::GameConfig::default_config_path_ = "resources/default_config.json";
std::unordered_map<std::string, std::string> slime_shooter::GameConfig::config_data_;
std::string slime_shooter::GameConfig::empty_property_value_;

}