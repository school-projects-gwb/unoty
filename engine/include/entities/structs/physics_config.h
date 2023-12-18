#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_PHYSICS_CONFIG_H
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_PHYSICS_CONFIG_H

#include "vector_2d.h"

namespace engine::physics {

struct PhysicsConfig {
  int steps_per_second;
  int velocity_iterations;
  int position_iterations;
  engine::entities::Vector2d gravity;
};

} //engine::physics

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_PHYSICS_CONFIG_H
