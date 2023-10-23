#ifndef ENGINE_INCLUDE_ENTITIES_SPRITE_H_
#define ENGINE_INCLUDE_ENTITIES_SPRITE_H_

#include "component.h"

namespace engine::entities {

/// @brief Contains logic for rendering sprite
class Sprite : Component {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_SPRITE_H_
