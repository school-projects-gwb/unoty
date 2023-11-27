#include "entities/ui/ui_button_callback_function.h"
#include "entities/ui/ui_button.h"
#include "entities/ui/ui_text.h"
#include <utility>
#include "iostream"

namespace engine::entities {

class UiButton::Impl : public GameObject {
 public:
  Impl(GameObject* owner, entities::UiButtonCallbackFunction callback_function) : owner_(owner) {
    callback_function_ = std::move(callback_function);
    transform_ = owner_->GetTransform();

    button_text_ = GameObject::Create<UiText>();
    button_text_->GetTransform()->Position = transform_->Position;

    button_background_ = GameObject::Create<UiObject>();
    button_background_->GetTransform()->Position = transform_->Position;
  }

  void Render(const std::unique_ptr<ui::Renderer> &renderer) {
    button_background_->Render(renderer);
    button_text_->Render(renderer);
  }

  void TriggerClick() {
    callback_function_();
  }

  void SetText(const std::string& text, const std::string &font_path, int font_size, entities::Color color) {
    button_text_->SetContent(text);
    button_text_->SetFont(font_path, font_size);
    button_text_->SetColor(color);
  }

  void SetRelativeTextPosition(entities::Point position) {
    auto background_position = button_background_->GetTransform()->Position;
    button_text_->GetTransform()->Position = {background_position.x + position.x, background_position.y + position.y};
  }

  void SetBackgroundColor(const entities::Color background_color) {
    button_background_->SetBackgroundColor(background_color);
  }

  void SetPosition(entities::Vector2d position) {
    transform_->Position = position;
    button_background_->GetTransform()->Position = position;
    button_text_->GetTransform()->Position = position;
  }

  void SetSize(entities::Point size) {
    button_background_->GetTransform()->SetSize(size);
    transform_->SetSize(size);
  }

 private:
  entities::UiButtonCallbackFunction callback_function_;
  std::shared_ptr<entities::UiText> button_text_;
  std::shared_ptr<entities::UiObject> button_background_;

  GameObject* owner_;
  std::shared_ptr<Transform> transform_;
};

UiButton::~UiButton() = default;
UiButton::UiButton(entities::UiButtonCallbackFunction callback_function) : impl_(new Impl(this, std::move(callback_function))) {}

void UiButton::Render(const std::unique_ptr<ui::Renderer> &renderer) {
  impl_->Render(renderer);
}

void UiButton::TriggerClick() {
  impl_->TriggerClick();
}

void UiButton::SetText(const std::string &text, const std::string &font_path, int font_size, entities::Color color) {
  impl_->SetText(text, font_path, font_size, color);
}

void UiButton::SetRelativeTextPosition(entities::Point position) {
  impl_->SetRelativeTextPosition(position);
}

void UiButton::SetBackgroundColor(const entities::Color background_color) {
  impl_->SetBackgroundColor(background_color);
}

void UiButton::SetPosition(entities::Vector2d position) {
  impl_->SetPosition(position);
}

void UiButton::SetSize(entities::Point size) {
  impl_->SetSize(size);
}

}