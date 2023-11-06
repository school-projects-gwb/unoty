#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_RECTANGLE_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_RECTANGLE_H_

namespace engine::entities {

/// @brief Used to store both position and width and height data
struct Rectangle {
  int x;
  int y;
  int w;
  int h;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_RECTANGLE_H_
