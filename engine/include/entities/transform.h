#ifndef ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_
#define ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_

#include <memory>
#include "entities/structs/point.h"

namespace engine::entities {

/// @brief Contains positional data for GameObject
class Transform {
 public:
  ~Transform();
  Transform();

  /// @brief Constructs Transform with position, rotation and scale included
  ///
  /// @overload
  Transform(Point position, float rotation, float scale);

  /// @brief Sets rotation (minimum and default of 0.0, maximum of 360.0)
  void SetRotation(double rotation);

  [[nodiscard]] double GetRotation() const;

  void SetScale(float scale);

  [[nodiscard]] float GetScale() const;

  /// @brief Sets Position of object; public property for easy access
  Point Position={0, 0};
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_
