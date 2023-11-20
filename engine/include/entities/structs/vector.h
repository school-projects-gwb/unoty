#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_VECTOR_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_VECTOR_H_

#include <iostream>
#include <cmath>

namespace engine::entities {

class Vector {
 public:
  float x;
  float y;

  Vector() : x(0.0f), y(0.0f) {}
  Vector(float xValue, float yValue) : x(xValue), y(yValue) {}

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

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_VECTOR_H_
