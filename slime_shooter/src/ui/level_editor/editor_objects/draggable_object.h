#ifndef SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_DRAGGABLE_OBJECT_H_
#define SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_DRAGGABLE_OBJECT_H_

#include "string"
#include "entities/structs/point.h"
#include "entities/game_object.h"

using namespace engine::entities;

namespace slime_shooter {

class DraggableObject : public GameObject {
 public:
  std::string key_name;
  std::string sprite_path;
  Vector2d position_in_editor;
};

}

#endif //SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_DRAGGABLE_OBJECT_H_
