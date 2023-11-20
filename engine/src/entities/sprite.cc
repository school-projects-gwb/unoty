#include <iostream>
#include "entities/sprite.h"
#include "entities/structs/sprite_flip.h"

namespace engine::entities {

class Sprite::Impl : public Component {
 public:
  Impl(std::string sprite_path) {
    sprite_path_ = sprite_path;
  }

  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<Transform> transform) const {
    ui::RenderInfo render_info;
    render_info.sprite_path = sprite_path_;
    render_info.transform = transform;
    render_info.size = transform->GetSize();

    if (!has_color_overlay_) {
      renderer->RenderSprite(render_info, {flip_});
    } else {
      renderer->RenderSpriteWithColorOverlay(render_info, {flip_, color_});
    }
  }

  void SetColor(entities::Color color) {
    int default_value = 255;
    if (color.r != default_value || color.g != default_value || color.b != default_value) {
      // Only set when Color isn't default color to prevent unnecessary color modulation application when rendering
      color_ = color;
      has_color_overlay_ = true;
    }
  }

  [[nodiscard]] entities::Color GetColor() const {
    return color_;
  }

  void SetFlip(entities::SpriteFlip flip) {
    flip_ = flip;
  }

  [[nodiscard]] entities::SpriteFlip GetFlip() const {
    return flip_;
  }

 private:
  std::string sprite_path_;
  bool has_color_overlay_ = false;
  entities::Color color_ = {255, 255, 255};
  entities::SpriteFlip flip_ = entities::SpriteFlip::FlipNone;
};

Sprite::~Sprite() = default;
Sprite::Sprite(std::string sprite_path) : impl_(new Impl(std::move(sprite_path))) {}

void Sprite::Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<Transform> transform) const {
  impl_->Render(renderer, transform);
}

void Sprite::SetColor(entities::Color color) {
  impl_->SetColor(color);
}

entities::Color Sprite::GetColor() const {
  return impl_->GetColor();
}

void Sprite::SetFlip(entities::SpriteFlip flip) {
  impl_->SetFlip(flip);
}

entities::SpriteFlip Sprite::GetFlip() const {
  return impl_->GetFlip();
}

}