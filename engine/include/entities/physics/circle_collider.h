#ifndef ENGINE_INCLUDE_ENTITIES_PHYSICS_CIRCLE_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_PHYSICS_CIRCLE_COLLIDER_H_

#include <memory>
#include "collider.h"

namespace engine::entities {

/// @brief Collider - circular shape
class CircleCollider : public Collider {
 public:
  explicit CircleCollider(float radius);
  ~CircleCollider();

  void SetRadius(float radius);
  [[nodiscard]] float GetRadius() const;

  [[nodiscard]] float GetFriction() const override;
  void SetFriction(float amount) override;

  [[nodiscard]] float GetDensity() const override;
  void SetDensity(float amount) override;

  [[nodiscard]] ColliderType GetType() const override;

  /// @brief Used for colliders that should only trigger OnCollision behavior, with the ability to pass through the colliding object.
  [[nodiscard]] bool GetIsSensor() const override;

  /// @brief Used for colliders that should only trigger OnCollision behavior, with the ability to pass through the colliding object.
  void SetIsSensor(bool value) override;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_PHYSICS_CIRCLE_COLLIDER_H_
