#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_PRECISE_POINT_H
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_PRECISE_POINT_H

namespace engine::entities {

/// @brief Stores two points with precise data type; such as width and height, or x and y coordinates
struct PrecisePoint {
  double x;
  double y;
};

}


#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_PRECISE_POINT_H
