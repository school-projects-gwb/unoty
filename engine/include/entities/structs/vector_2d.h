#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_VECTOR2D_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_VECTOR2D_H_

#include <iostream>
#include <cmath>

namespace engine::entities {

class Vector2d {
 public:
  float x;
  float y;

  Vector2d() : x(0.0f), y(0.0f) {}
  Vector2d(float x_value, float y_value) : x(x_value), y(y_value) {}
  Vector2d(int x_value, int y_value) : x((float) x_value), y((float) y_value) {}

  // Magnitude (length) of the vector
  float magnitude() const {
    return std::sqrt(x * x + y * y);
  }

  void normalize() {
    float mag = magnitude();
    if (mag != 0.0f) {
      x /= mag;
      y /= mag;
    }
  }
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_VECTOR2D_H_
