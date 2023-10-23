#ifndef ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_
#define ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_

#include "component.h"

namespace engine::entities {

/// @brief Contains logic to animate sprites
class Animator : Component {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_
