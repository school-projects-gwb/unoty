#include "data_handler/serializer.h"
#include "json_serializer.h"
#include <nlohmann/json.hpp>

namespace engine::data_handler {

std::string JsonSerializer::Serialize(const DataObject& data_object) {
  nlohmann::json nlohmann_json;

  for (const auto& data : data_object.GetData()) {
    const auto& key = data.first;
    const auto& value = data.second;

    std::visit([&nlohmann_json, &key, this](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double> ||
          std::is_same_v<T, bool> || std::is_same_v<T, std::string>) {
        nlohmann_json[key] = arg;
      } else if constexpr (std::is_same_v<T, std::vector<DataObject>>) {
        for (const auto& elem : arg) {
          nlohmann_json[key].push_back(nlohmann::json::parse(Serialize(elem)));
        }
      } else if constexpr (std::is_same_v<T, DataObject>) {
        nlohmann_json[key] = nlohmann::json::parse(Serialize(arg));
      } else if constexpr (
          std::is_same_v<T, std::vector<std::string>> ||
          std::is_same_v<T, std::vector<int>> ||
          std::is_same_v<T, std::vector<double>> ||
          std::is_same_v<T, std::vector<bool>>) {
        nlohmann_json[key] = arg;
      }
    }, value);
  }

  return nlohmann_json.dump();
}


DataObject JsonSerializer::Deserialize(const std::string& data_stream) {
  nlohmann::json nlohmann_json = nlohmann::json::parse(data_stream);
  DataObject data_object;

  for (auto& [key, value] : nlohmann_json.items()) {
    if (value.is_string()) {
      data_object.SetValue(key, value.get<std::string>());
    } else if (value.is_number_integer()) {
      data_object.SetValue(key, value.get<int>());
    } else if (value.is_number_float()) {
      data_object.SetValue(key, value.get<double>());
    } else if (value.is_boolean()) {
      data_object.SetValue(key, value.get<bool>());
    } else if (value.is_array()) {
      if (!value.empty()) {
        if (value[0].is_string()) {
          std::vector<std::string> vec = value.get<std::vector<std::string>>();
          data_object.SetValue(key, vec);
        } else if (value[0].is_number_integer()) {
          std::vector<int> vec = value.get<std::vector<int>>();
          data_object.SetValue(key, vec);
        } else if (value[0].is_number_float()) {
          std::vector<double> vec = value.get<std::vector<double>>();
          data_object.SetValue(key, vec);
        } else if (value[0].is_boolean()) {
          std::vector<bool> vec = value.get<std::vector<bool>>();
          data_object.SetValue(key, vec);
        } else if (value[0].is_object()) {
          std::vector<DataObject> vec;
          for (auto& elem : value) {
            vec.push_back(Deserialize(elem.dump()));
          }
          data_object.SetValue(key, vec);
        }
      }
    } else if (value.is_object()) {
      data_object.SetValue(key, Deserialize(value.dump()));
    }
  }

  return data_object;
}


}