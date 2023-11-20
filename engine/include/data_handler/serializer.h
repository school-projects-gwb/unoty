#ifndef ENGINE_SRC_DATA_HANDLER_SERIALIZER_H_
#define ENGINE_SRC_DATA_HANDLER_SERIALIZER_H_

#include <mutex>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "data_object.h"
#include "serializer_interface.h"

namespace engine::data_handler {

/// @brief Enum class for defining serializer types.
enum class SerializerType{
  Json  ///< Represents a JSON serializer.
};

/// @brief Serializer class provides static methods for serializing and deserializing
///        DataObjects using various serialization strategies defined by SerializerType.
class Serializer {
 public:
  /// @brief Serializes a DataObject into a string based on the specified serializer type.
  /// @param type The type of serializer to use, defined in SerializerType.
  /// @param data_object The DataObject to Serialize.
  /// @return A string representation of the serialized DataObject.
  static std::string Serialize(SerializerType type, const DataObject& data_object);

  /// @brief Deserializes data from a string into a DataObject based on the specified serializer type.
  /// @param type The type of serializer to use, defined in SerializerType.
  /// @param data_stream The string representation of the data to Deserialize.
  /// @return A DataObject that represents the deserialized data.
  static DataObject Deserialize(SerializerType type, const std::string& data_stream);

  // Deleted constructors and assignment operators for making the class non-instantiable.
  Serializer() = delete;
  ~Serializer() = delete;
  Serializer(const Serializer&) = delete;
  Serializer& operator=(const Serializer&) = delete;

 private:
  /// @brief Initializes the map of serializers for each SerializerType.
  /// @return A map of SerializerType to their corresponding SerializerInterface unique pointers.
  static std::map<SerializerType, std::unique_ptr<SerializerInterface>> InitializeSerializers();

  /// @brief Provides access to the map of serializers.
  /// @return A reference to the map of SerializerType to SerializerInterface.
  static std::map<SerializerType, std::unique_ptr<SerializerInterface>> &GetSerializers();
};

}

#endif //ENGINE_SRC_DATA_HANDLER_SERIALIZER_H_