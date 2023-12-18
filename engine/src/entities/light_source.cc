#include "entities/light_source.h"
#include "utility/timer.h"
#include <cmath>

namespace engine::entities {

class LightSource::Impl : public Component {
 public:
  explicit Impl(std::string sprite_path) : sprite_(sprite_path), sprite_path_(sprite_path) {}

  void Render(const std::unique_ptr<ui::SpriteRenderer> &renderer,
              const std::shared_ptr<entities::Transform>& transform) {
    ui::RenderInfo render_info;
    render_info.sprite_path = sprite_path_;
    render_info.transform = transform;
    render_info.size = transform->GetSize();
    render_info.is_ui_object = true;

    if (!sprite_.HasColorOverlay()) {
      renderer->RenderSprite(render_info, {sprite_.GetFlip()});
    } else {
      renderer->RenderSpriteWithColorOverlay(render_info, {sprite_.GetFlip(), sprite_.GetColor()});
    }
  }

  [[nodiscard]] entities::Sprite &GetSprite() {
    return sprite_;
  }
 private:
  Sprite sprite_;
  std::string sprite_path_;
  utility::Timer timer_;
};

void LightSource::Render(const std::unique_ptr<ui::SpriteRenderer> &renderer,
                         const std::shared_ptr<entities::Transform>& transform) {
  impl_->Render(renderer, transform);
}

LightSource::~LightSource() = default;

LightSource::LightSource(std::string sprite_path) : impl_(std::make_unique<Impl>(sprite_path)) {}

entities::Sprite &LightSource::GetSprite() {
  return impl_->GetSprite();
}

}