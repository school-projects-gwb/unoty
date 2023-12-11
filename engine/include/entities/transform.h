#ifndef ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_
#define ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_

#include <memory>
#include "entities/structs/point.h"
#include "entities/structs/vector_2d.h"

namespace engine::entities {

/// @brief Contains positional data for GameObject
class Transform {
 public:
  ~Transform();
  Transform();

  /// @brief Constructs Transform with position, rotation and scale included
  ///
  /// @overload
  Transform(Vector2d position, float rotation, float scale);

  /// @brief Sets rotation (minimum and default of 0.0, maximum of 360.0)
  void SetRotation(double rotation);
  [[nodiscard]] double GetRotation() const;

  void SetScale(float scale);
  [[nodiscard]] float GetScale() const;

  /// @brief Set size that all components in object can use for consistent/relative sizing
  void SetSize(entities::Point size);
  [[nodiscard]] entities::Point GetSize() const;

  /// @brief Get size of calculated size * scale
  [[nodiscard]] entities::Point GetScaledSize() const;

  /// @brief Sets Position of object; public property for easy access
  /// If the gameobject has a rigidbody, assigning a new position should be done via the rigidbody.
  /// Otherwise the next physics step will overwrite it with calculations based on the rigidbodies position.
  Vector2d Position={0, 0};

  /// @brief calculate the center position point (positions - (size/2))
  [[nodiscard]] entities::Point GetCenterPosition() const {
    entities::Point center;
    center.x = Position.x + (GetScaledSize().x / 2);
    center.y = Position.y + (GetScaledSize().y / 2);
    return center;
  }

  /// @brief Checks whether given position is "inside" Transform by comparing Transform's width, height, x- and y positions.
  [[nodiscard]] bool IsInPositionBounds(entities::Vector2d position) const {
    bool in_bounds_x = position.x >= Position.x && position.x <= Position.x + GetScaledSize().x;
    bool in_bounds_y = position.y >= Position.y && position.y <= Position.y + GetScaledSize().y;

    return in_bounds_x && in_bounds_y;
  }

 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_TRANSFORM_H_
