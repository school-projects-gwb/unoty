#ifndef ENGINE_INCLUDE_ENTITIES_CAMERA_H_
#define ENGINE_INCLUDE_ENTITIES_CAMERA_H_

#include "entities/game_object.h"

namespace engine::entities {

/// @brief Contains logic to follow certain objects
class Camera : GameObject {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_CAMERA_H_
