#ifndef ENGINE_INCLUDE_ENTITIES_UI_OBJECT_H_
#define ENGINE_INCLUDE_ENTITIES_UI_OBJECT_H_

#include "entities/game_object.h"

namespace engine::entities {

/// @brief Base ui object containing size information
class UiObject : GameObject {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_UI_OBJECT_H_
