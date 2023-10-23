#ifndef ENGINE_INCLUDE_ENTITIES_RIGID_BODY_H_
#define ENGINE_INCLUDE_ENTITIES_RIGID_BODY_H_

#include "component.h"

namespace engine::entities {

/// @brief Contains logic for Component gravity
class RigidBody : Component {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_RIGID_BODY_H_
