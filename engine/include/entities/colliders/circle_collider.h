#ifndef ENGINE_INCLUDE_ENTITIES_COLLIDERS_CIRCLE_COLLIDER_H_
#define ENGINE_INCLUDE_ENTITIES_COLLIDERS_CIRCLE_COLLIDER_H_

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

#endif //ENGINE_INCLUDE_ENTITIES_COLLIDERS_CIRCLE_COLLIDER_H_
