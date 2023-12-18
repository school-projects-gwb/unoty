#ifndef ENGINE_INCLUDE_ENTITIES_SPRITE_H_
#define ENGINE_INCLUDE_ENTITIES_SPRITE_H_

#include "component.h"
#include "rendering/renderer.h"
#include "entities/structs/sprite_flip.h"

namespace engine::entities {

/// @brief Contains logic and data for rendering sprite
class Sprite : public Component {
 public:
  explicit Sprite(std::string sprite_path);
  ~Sprite();

  virtual void Render(const std::unique_ptr<ui::SpriteRenderer> &renderer, const std::shared_ptr<entities::Transform> &transform) const;

  void SetColor(entities::Color color);
  [[nodiscard]] entities::Color GetColor() const;
  [[nodiscard]] bool HasColorOverlay() const;

  void SetFlip(entities::SpriteFlip flip);
  [[nodiscard]] entities::SpriteFlip GetFlip() const;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_SPRITE_H_
