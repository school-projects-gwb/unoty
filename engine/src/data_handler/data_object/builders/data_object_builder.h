#ifndef ENGINE_SRC_DATA_HANDLER_DATA_OBJECT_BUILDERS_DATA_OBJECT_BUILDER_H
#define ENGINE_SRC_DATA_HANDLER_DATA_OBJECT_BUILDERS_DATA_OBJECT_BUILDER_H

#include "data_handler/data_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "entities/audio_source.h"
namespace engine::data_handler {

class DataObjectBuilder {
 public:
  DataObjectBuilder();

  DataObjectBuilder& WithScriptName(const engine::entities::GameObject& game_object);
  DataObjectBuilder& WithTransform(const engine::entities::GameObject& game_object);

  DataObject Build();
 private:
  std::shared_ptr<DataObject> data_object_;
};
}
#endif //ENGINE_SRC_DATA_HANDLER_DATA_OBJECT_BUILDERS_DATA_OBJECT_BUILDER_H
