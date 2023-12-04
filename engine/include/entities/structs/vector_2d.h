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
  [[nodiscard]] float Magnitude() const {
    return std::sqrt(x * x + y * y);
  }

  void Normalize() {
    float mag = Magnitude();
    if (mag != 0.0f) {
      x /= mag;
      y /= mag;
    }
  }

  [[nodiscard]] float Distance(const Vector2d& other) const {
    float distance_x = x - other.x;
    float distance_y = y - other.y;
    return std::sqrt(distance_x * distance_x + distance_y * distance_y);
  }
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_VECTOR2D_H_
