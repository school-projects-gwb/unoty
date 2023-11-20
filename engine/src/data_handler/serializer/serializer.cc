#include "data_handler/serializer.h"
#include "data_handler/serializer/json/json_serializer.h"

namespace engine::data_handler {

std::map<SerializerType, std::unique_ptr<SerializerInterface>> Serializer::InitializeSerializers() {
  std::map<SerializerType, std::unique_ptr<SerializerInterface>> serializers;
  serializers[SerializerType::Json] = std::make_unique<JsonSerializer>();
  return serializers;
}

std::map<SerializerType, std::unique_ptr<SerializerInterface>>& Serializer::GetSerializers() {
  static std::map<SerializerType, std::unique_ptr<SerializerInterface>> serializers = InitializeSerializers();
  return serializers;
}

std::string Serializer::Serialize(SerializerType type, const DataObject& data_object) {
  auto& serializers = GetSerializers();
  auto it = serializers.find(type);
  if (it != serializers.end()) {
    return it->second->Serialize(data_object);
  }
  throw std::runtime_error("Serializer for the specified type not found for serialization.");
}

DataObject Serializer::Deserialize(SerializerType type, const std::string& data_stream) {
  auto& serializers = GetSerializers();
  auto it = serializers.find(type);

  if (it != serializers.end()) {
    return it->second->Deserialize(data_stream);
  }
  throw std::runtime_error("Serializer for the specified type not found for deserialization.");
}

}
