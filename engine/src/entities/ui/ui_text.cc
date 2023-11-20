#include "entities/ui/ui_text.h"
#include "iostream"

namespace engine::entities {

class UiText::Impl : public UiObject {
 public:
  Impl(GameObject *owner) : owner_(owner) {
    transform_ = owner_->GetTransform();
  }

  void Render(const std::unique_ptr<ui::Renderer> &renderer) override {
    auto &text_renderer = renderer->GetTextRenderer();

    auto render_info = ui::TextRenderInfo();
    render_info.font_path = font_path_;
    render_info.font_size = font_size_;
    render_info.content = content_;
    render_info.target_position = transform_->Position;
    render_info.text_color = color_;

    text_renderer->RenderText(render_info);
  }

  void SetContent(const std::string& content) {
    content_ = content;
  }

  const std::string& GetContent() const {
    return content_;
  }

  void SetFont(const std::string& font_path, int font_size = 12) {
    font_path_ = font_path;
    font_size_ = font_size;
  }

  const std::string& GetFont() const {
    return font_path_;
  }

  void SetAlignment(int alignment) {
    alignment_ = alignment;
  }

  int GetAlignment() const {
    return alignment_;
  }

  void SetColor(entities::Color color) {
    color_ = color;
  }

  entities::Color GetColor() const {
    return color_;
  }

 private:
  std::string content_;
  std::string font_path_;
  int alignment_ = 0;
  entities::Color color_ = {255, 255, 255};
  int font_size_ = 12;

  GameObject* owner_;
  std::shared_ptr<Transform> transform_;
};

UiText::~UiText() = default;
UiText::UiText() : impl_(new Impl(this)) {}

void UiText::Render(const std::unique_ptr<ui::Renderer> &renderer) {
  impl_->Render(renderer);
}

void UiText::SetContent(const std::string &content) {
  impl_->SetContent(content);
}

const std::string &UiText::GetContent() const {
  return impl_->GetContent();
}

void UiText::SetFont(const std::string &font_path, int font_size) {
  impl_->SetFont(font_path, font_size);
}

const std::string &UiText::GetFont() const {
  return impl_->GetFont();
}

void UiText::SetAlignment(int alignment) {
  impl_->SetAlignment(alignment);
}

int UiText::GetAlignment() const {
  return impl_->GetAlignment();
}

void UiText::SetColor(entities::Color color) {
  impl_->SetColor(color);
}

entities::Color UiText::GetColor() const {
  return impl_->GetColor();
}

}