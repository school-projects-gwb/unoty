#ifndef SLIME_SHOOTER_SRC_CONFIG_SLIME_SHOOTER_SRC_CONFIG_GAME_CONFIG_H_
#define SLIME_SHOOTER_SRC_CONFIG_SLIME_SHOOTER_SRC_CONFIG_GAME_CONFIG_H_

#include "string"
#include "unordered_map"
#include "data_handler/file_handler/file_handler.h"
#include "data_handler/serializer.h"

namespace slime_shooter {

class GameConfig {
 public:
  static void SetPropertyValue(const std::string& property_name, const std::string& property_value) {
    auto config_file_data = engine::data_handler::FileHandler::GetInstance().ReadFile(default_config_path_);
    auto deserialized_config = engine::data_handler::Serializer::Deserialize(engine::data_handler::SerializerType::Json,
                                                                             config_file_data);

    deserialized_config.SetValue(property_name, property_value);
    auto serialized_config = engine::data_handler::Serializer::Serialize(
        engine::data_handler::SerializerType::Json, deserialized_config);
    engine::data_handler::FileHandler::GetInstance().WriteFile(default_config_path_, serialized_config);

    ReloadConfig();
  }

  static const std::string &GetPropertyValue(const std::string& property_name) {
    try {
      return config_data_.at(property_name);
    } catch (const std::out_of_range& e) {
      return empty_property_value_;
    }
  }

  static void ReloadConfig() {
    auto config_file_data = engine::data_handler::FileHandler::GetInstance().ReadFile(default_config_path_);
    auto deserialized_config = engine::data_handler::Serializer::Deserialize(engine::data_handler::SerializerType::Json,
                                                                            config_file_data);

    for (auto value : deserialized_config.GetData())
      if (std::holds_alternative<std::string>(value.second))
        config_data_[value.first] = std::get<std::string>(value.second);
  }

 private:
  static std::string default_config_path_;
  static std::unordered_map<std::string, std::string> config_data_;
  static std::string empty_property_value_;
};

}

#endif //SLIME_SHOOTER_SRC_CONFIG_SLIME_SHOOTER_SRC_CONFIG_GAME_CONFIG_H_
