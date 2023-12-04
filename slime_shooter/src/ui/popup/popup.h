#ifndef SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_H_
#define SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_H_

#include "entities/game_object.h"
#include "engine/engine_config.h"
#include "entities/structs/vector_2d.h"
#include "entities/ui/ui_object.h"
#include "popup_title.h"
#include "popup_content.h"

using namespace engine::entities;

struct PopupConfig {
  Vector2d title_position_ = {engine::EngineConfig::window_width/2 - 195, 215};
  Vector2d content_position_ = {engine::EngineConfig::window_width/2 - 195, 250};
};

namespace slime_shooter {

class Popup : public GameObject {
 public:
  Popup() {
    int window_width = engine::EngineConfig::window_width;
    int window_height = engine::EngineConfig::window_height;
    int popup_width = static_cast<int>(engine::EngineConfig::window_width * 0.6);
    int popup_height = static_cast<int>(engine::EngineConfig::window_height * 0.5);

    auto background = GameObject::Create<UiObject>();
    background->SetBackgroundColor(Color{0, 0, 0, 150});
    background->GetTransform()->SetSize({window_width, window_height});

    auto foreground = GameObject::Create<UiObject>();
    foreground->SetBackgroundColor(GameColor::Ui::BackgroundDark);
    foreground->GetTransform()->SetSize({popup_width, popup_height});
    foreground->GetTransform()->Position = Vector2d{(window_width - popup_width) / 2, (window_height - popup_height) / 2};

    popup_title_ = GameObject::Create<PopupTitle>();
    popup_content_ = GameObject::Create<PopupContent>();

    auto popup_continue_text = GameObject::Create<UiText>();
    popup_continue_text->SetColor(GameColor::Ui::TextRed);
    popup_continue_text->SetContent("PRESS <SPACE> TO CONTINUE");
    popup_continue_text->SetFont(GameFont::Default, 24);
    popup_continue_text->GetTransform()->Position = {engine::EngineConfig::window_width/2 - 295, 450};

    AddChildObject(background);
    AddChildObject(foreground);
    AddChildObject(popup_title_);
    AddChildObject(popup_content_);
    AddChildObject(popup_continue_text);

    SetName("popup");
    SetIsActive(false);
  }

  void Show(const std::string &title, const std::string &content, PopupConfig popup_config) {
    if (GetIsActive()) return; // Check whether popup is already active

    SetIsActive(true);

    popup_title_->UpdateContent(title, popup_config.title_position_);
    popup_content_->UpdateContent(content, popup_config.content_position_);

    engine::Engine::GetInstance().Pause([this]() { Hide(); });
  }

  void Hide() {
    if (!GetIsActive() || !Input::HasPressedKey(Key::UnoSpace)) return;

    SetIsActive(false);
    engine::EngineConfig::is_paused = false;
  }

 private:
  std::shared_ptr<PopupTitle> popup_title_;
  std::shared_ptr<PopupContent> popup_content_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_H_
