#ifndef ENGINE_SRC_DATA_HANDLER_SERIALIZER_JSON_SERIALIZER_H_
#define ENGINE_SRC_DATA_HANDLER_SERIALIZER_JSON_SERIALIZER_H_

#include "data_handler/serializer_interface.h"
#include "data_handler/data_object.h"

namespace engine::data_handler {

class JsonSerializer : public SerializerInterface {
  std::string Serialize(const DataObject& data_object) override;
  DataObject Deserialize(const std::string& data_stream) override;
};

}

#endif //ENGINE_SRC_DATA_HANDLER_SERIALIZER_JSON_SERIALIZER_H_
