#include "entities/scene/scene_lighting.h"

namespace engine::entities {

class SceneLighting::Impl {
 public:
  explicit Impl(entities::Color lighting_color) : lighting_color_(lighting_color) {
  }

  void StartRenderLighting(const std::unique_ptr<engine::ui::SpriteRenderer> &sprite_renderer) const {
    sprite_renderer->StartLightLayer(lighting_color_);
  }

  void SetLightingColor(entities::Color lighting_color) {
    lighting_color_ = lighting_color;
  }
 private:
  entities::Color lighting_color_;
};

SceneLighting::SceneLighting(entities::Color lighting_color) : impl_(new Impl(lighting_color)) {}
SceneLighting::~SceneLighting() = default;

void SceneLighting::StartRenderLighting(const std::unique_ptr<engine::ui::SpriteRenderer> &sprite_renderer) const {
  impl_->StartRenderLighting(sprite_renderer);
}

void SceneLighting::SetLightingColor(entities::Color lighting_color) {
  impl_->SetLightingColor(lighting_color);
}

}