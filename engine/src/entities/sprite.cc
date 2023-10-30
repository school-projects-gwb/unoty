#include <iostream>
#include "entities/sprite.h"

namespace engine::entities {

class Sprite::Impl : public Component {
 public:
  Impl(std::string sprite_path) {
    sprite_path_ = sprite_path;
  }

  void Render(const std::unique_ptr<engine::ui::Renderer>& renderer, Point& position) {
    renderer->RenderSprite(sprite_path_, position);
  }

 private:
  std::string sprite_path_;
};

Sprite::~Sprite() = default;
Sprite::Sprite(std::string sprite_path) : impl_(new Impl(std::move(sprite_path))) {}

void Sprite::Render(const std::unique_ptr<engine::ui::Renderer>& renderer, Point& position) {
  impl_->Render(renderer, position);
}

}