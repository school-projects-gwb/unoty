#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_POINT_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_POINT_H_

namespace engine::entities {

/// @brief Stores two points; such as width and height, or x and y coordinates
struct Point {
  int x;
  int y;

  Point operator /(int v) const {
    return {x/v, y/v};
  }
  Point operator *(int v) const {
    return {x*v, y*v};
  }
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_POINT_H_
