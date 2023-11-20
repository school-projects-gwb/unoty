#include "entities/ui/ui_object.h"

namespace engine::entities {

class UiObject::Impl : public GameObject {
 public:
  Impl(GameObject* owner) : owner_(owner) {
    transform_ = owner_->GetTransform();
  }

  void Render(const std::unique_ptr<ui::Renderer> &renderer) {
    auto &sprite_renderer = renderer->GetSpriteRenderer();

    ui::RenderInfo render_info;
    render_info.target_position.x = transform_->Position.x;
    render_info.target_position.y = transform_->Position.y;
    render_info.target_position.w = transform_->GetSize().x;
    render_info.target_position.h = transform_->GetSize().y;
    render_info.size = transform_->GetSize();

    if (sprite_path_.empty()) {
      sprite_renderer->RenderRectangle(render_info, {FlipNone, background_color_});
      return;
    }

    render_info.transform = transform_;
    render_info.sprite_path = sprite_path_;

    sprite_renderer->RenderSprite(render_info, {{},{}, true});
  }

  void SetBackgroundColor(entities::Color background_color) {
    background_color_ = background_color;
  }

  entities::Color GetBackgroundColor() const {
    return background_color_;
  }

  void SetSpritePath(const std::string &sprite_path) {
    sprite_path_ = sprite_path;
  }

 private:
  entities::Color background_color_ = {255, 255, 255};
  std::string sprite_path_;

  GameObject* owner_;
  std::shared_ptr<Transform> transform_;
};

UiObject::~UiObject() = default;
UiObject::UiObject() : impl_(new Impl(this)) {}

void UiObject::Render(const std::unique_ptr<ui::Renderer> &renderer) {
  impl_->Render(renderer);
}

void UiObject::SetBackgroundColor(entities::Color background_color) {
  impl_->SetBackgroundColor(background_color);
}

entities::Color UiObject::GetBackgroundColor() const {
  return impl_->GetBackgroundColor();
}

void UiObject::SetSpritePath(const std::string &sprite_path) {
  impl_->SetSpritePath(sprite_path);
}

}