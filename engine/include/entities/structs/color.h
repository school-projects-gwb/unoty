#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_COLOR_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_COLOR_H_

namespace engine::entities {

/// @brief Color struct for Red, Green, Blue and A (transparency) values
struct Color {
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
  unsigned char a = 255;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_COLOR_H_
