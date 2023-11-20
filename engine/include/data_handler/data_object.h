
#ifndef ENGINE_INCLUDE_DATA_HANDLER_DATA_OBJECT_H_
#define ENGINE_INCLUDE_DATA_HANDLER_DATA_OBJECT_H_

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "entities/game_object.h"

namespace engine::data_handler {

class DataObject;

/// @brief Type alias for a variant that can hold different types of data values.
using VariantValue = std::variant<
    std::string,
    int,
    double,
    bool,
    DataObject,
    std::vector<std::string>,
    std::vector<int>,
    std::vector<double>,
    std::vector<bool>,
    std::vector<DataObject>
>;

/// @brief Represents a flexible data structure that can hold various types of data.
///        It can store basic data types like strings, integers, doubles, booleans,
///        as well as nested DataObject instances and arrays of DataObjects.
class DataObject {
 public:
  /// @brief Constructor for DataObject, initializes internal structures for data storage.
  DataObject();

  /// @brief Sets a value associated with a key in the DataObject.
  /// @param key A string representing the key.
  /// @param value The value to set, which can be any of the types defined in VariantValue.
  void SetValue(const std::string& key, const VariantValue& value);

  /// @brief Retrieves the value associated with a given key.
  /// @param key A string representing the key to search for.
  /// @return The value associated with the key.
  /// @throws std::runtime_error if the key is not found.
  [[nodiscard]] const VariantValue& GetValue(const std::string& key) const;

  /// @brief Removes a key-value pair from the DataObject.
  /// @param key A string representing the key to be removed.
  /// @throws std::runtime_error if the key is not found.
  void RemoveKey(const std::string& key);

  /// @brief Provides read-only access to the internal data of the DataObject.
  /// @return A const reference to the unordered_map containing the data.
  [[nodiscard]] const std::unordered_map<std::string, VariantValue>& GetData() const;

  /// @brief Static method to parse a GameObject into a DataObject.
  /// @param object The GameObject to be parsed.
  /// @return A DataObject representation of the GameObject.
  static DataObject Parse(const entities::GameObject& object);

  /// @brief Sets an array value associated with a key in the DataObject.
  ///        Converts a C-style array to a std::vector and stores it.
  /// @param key A string representing the key.
  /// @param array The C-style array to be set.
  /// @tparam T The type of elements in the array.
  /// @tparam N The number of elements in the array.
  template <typename T, size_t N>
  void SetArrayValue(const std::string& key, T (&array)[N]) {
    std::vector<T> vec(array, array + N);
    SetValue(key, vec);
  }
 private:
  class Impl;
  std::shared_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_DATA_HANDLER_DATA_OBJECT_H_
