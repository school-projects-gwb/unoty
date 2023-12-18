#ifndef ENGINE_INCLUDE_ENTITIES_PHYSICS_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_PHYSICS_COLLIDER_H_

#include "entities/component.h"

namespace engine::entities {

enum class ColliderType {
  Box, Circle
};

/// @brief Base for colliders
class Collider : public Component {
 public:
  virtual ~Collider() = default;

  /// @brief Used internally for type checking purposes
  [[nodiscard]] virtual ColliderType GetType() const = 0;

  [[nodiscard]] virtual float GetFriction() const = 0;
  virtual void SetFriction(float amount) = 0;

  [[nodiscard]] virtual float GetDensity() const = 0;
  virtual void SetDensity(float amount) = 0;

  /// @brief Used for colliders that should only trigger OnCollision behavior, with the ability to pass through the colliding object.
  [[nodiscard]] virtual bool GetIsSensor() const = 0;

  /// @brief Used for colliders that should only trigger OnCollision behavior, with the ability to pass through the colliding object.
  virtual void SetIsSensor(bool value) = 0;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_PHYSICS_COLLIDER_H_
