#ifndef ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_
#define ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_

#include "entities/structs/point.h"
#include <memory>

namespace engine::entities {

/// @brief Contains positional data for GameObject
class Transform {
 public:
  ~Transform();
  Transform();

  void SetRotation(float rotation);
  float GetRotation();

  void SetScale(float scale);
  float GetScale();

  Point Position= {0, 0};
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_
