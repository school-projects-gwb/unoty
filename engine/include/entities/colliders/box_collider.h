#ifndef ENGINE_INCLUDE_ENTITIES_COLLIDERS_BOX_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_COLLIDERS_BOX_COLLIDER_H_

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

  [[nodiscard]] float GetFriction() const;
  void SetFriction(float amount);

  [[nodiscard]] float GetDensity() const;
  void SetDensity(float amount);

  [[nodiscard]] ColliderType GetType() const override;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_COLLIDERS_BOX_COLLIDER_H_
