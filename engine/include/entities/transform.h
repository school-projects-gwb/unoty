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

  /// @brief Set size that all components in object can use for consistent/relative sizing
  void SetSize(entities::Point size);
  entities::Point GetSize() const;

  /// @brief Sets Position of object; public property for easy access
  Point Position={0, 0};

  /// @brief Checks whether given position is "inside" Transform by comparing Transform's width, height, x- and y positions.
  bool IsInPositionBounds(entities::Point position) const {
    bool in_bounds_x = position.x >= Position.x && position.x <= Position.x + GetSize().x;
    bool in_bounds_y = position.y >= Position.y && position.y <= Position.y + GetSize().y;

    return in_bounds_x && in_bounds_y;
  }
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_
