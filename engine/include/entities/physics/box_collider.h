#ifndef ENGINE_INCLUDE_ENTITIES_PHYSICS_BOX_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_PHYSICS_BOX_COLLIDER_H_

#include <memory>
#include "collider.h"

namespace engine::entities {

/// @brief Collider - box/square shape
class BoxCollider : public Collider {
 public:
  explicit BoxCollider(Vector2d size);
  ~BoxCollider() override;

  [[nodiscard]] Vector2d GetSize() const;
  void SetSize(Vector2d size);

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

#endif //ENGINE_INCLUDE_ENTITIES_PHYSICS_BOX_COLLIDER_H_
