#ifndef ENGINE_SRC_DATA_HANDLER_SERIALIZER_SERIALIZER_INTERFACE_H_
#define ENGINE_SRC_DATA_HANDLER_SERIALIZER_SERIALIZER_INTERFACE_H_

#include <string>
#include "data_handler/data_object.h"

namespace engine::data_handler {

class SerializerInterface {
 public:
  virtual ~SerializerInterface() = default;

  virtual std::string Serialize(const DataObject& data_object) = 0;
  virtual DataObject Deserialize(const std::string& data_stream) = 0;
};

}

#endif //ENGINE_SRC_DATA_HANDLER_SERIALIZER_SERIALIZER_INTERFACE_H_
