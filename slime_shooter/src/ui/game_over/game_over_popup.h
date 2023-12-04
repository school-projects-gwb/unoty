#ifndef SLIME_SHOOTER_SRC_UI_GAME_OVER_SLIME_SHOOTER_SRC_UI_GAME_OVER_GAME_OVER_POPUP_H_
#define SLIME_SHOOTER_SRC_UI_GAME_OVER_SLIME_SHOOTER_SRC_UI_GAME_OVER_GAME_OVER_POPUP_H_

#include "entities/game_object.h"
#include "engine/engine.h"
#include "engine/engine_config.h"
#include "entities/ui/ui_object.h"
#include "common/definitions.h"
#include "entities/ui/ui_text.h"
#include "statistics/statistics.h"

using namespace engine::entities;

namespace slime_shooter {

class GameOverPopup : public GameObject {
 public:
  GameOverPopup() {
    int window_width = engine::EngineConfig::window_width;
    int window_height = engine::EngineConfig::window_height;

    auto background = GameObject::Create<UiObject>();
    background->SetBackgroundColor(Color{0, 0, 0, 150});
    background->GetTransform()->SetSize({window_width, window_height});

    auto game_over_text = GameObject::Create<UiText>();
    game_over_text->SetColor(GameColor::Ui::TextGreen);
    game_over_text->SetContent("GAME OVER!");
    game_over_text->SetFont(GameFont::Default, 36);
    game_over_text->GetTransform()->Position = {engine::EngineConfig::window_width/2 - 170, 200};

    score_text_ = GameObject::Create<UiText>();
    score_text_->SetColor(GameColor::Ui::TextPink);
    score_text_->SetContent(".");
    score_text_->SetFont(GameFont::Default, 18);
    score_text_->GetTransform()->Position = {engine::EngineConfig::window_width/2 - 125, 275};

    play_again_button_ = GameObject::Create<UiButton>([]() {});
    play_again_button_->SetText("PLAY AGAIN (PRESS 1)", GameFont::Default, 14, GameColor::Ui::PrimaryButtonText);
    play_again_button_->SetBackgroundColor(GameColor::Ui::PrimaryButtonBackground);
    play_again_button_->SetSize({360, 60});
    play_again_button_->SetPosition({engine::EngineConfig::window_width/2 - 180, 325});
    play_again_button_->SetRelativeTextPosition({40, 25});
    play_again_button_->SetTagName("button");

    exit_to_menu_button_ = GameObject::Create<UiButton>([]() {});
    exit_to_menu_button_->SetText("EXIT TO MENU (PRESS 2)", GameFont::Default, 14, GameColor::Ui::SecondaryButtonText);
    exit_to_menu_button_->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    exit_to_menu_button_->SetSize({360, 60});
    exit_to_menu_button_->SetPosition({engine::EngineConfig::window_width/2 - 180, 400});
    exit_to_menu_button_->SetRelativeTextPosition({30, 25});
    exit_to_menu_button_->SetTagName("button");

    AddChildObject(background);
    AddChildObject(game_over_text);
    AddChildObject(score_text_);
    AddChildObject(play_again_button_);
    AddChildObject(exit_to_menu_button_);

    SetName("game_over_popup");
    SetIsActive(false);
  }

  void Show() {
    if (GetIsActive()) return; // Check whether popup is already active
    SetIsActive(true);

    auto player = GameObject::GetSceneObjectByName("Player");
    auto player_statistics = player->GetComponentByType<Statistics>();

    score_text_->SetContent("YOUR SCORE: " + std::to_string(player_statistics->GetInt(StatisticType::Score)));

    engine::Engine::GetInstance().Pause([this]() { Hide(); });
  }

  void Hide() {
    if (!GetIsActive() || (!Input::HasPressedKey(Key::Uno1) && !Input::HasPressedKey(Key::Uno2))) return;

    bool play_again = Input::HasPressedKey(Key::Uno1);
    SetIsActive(false);
    engine::EngineConfig::is_paused = false;
    engine::Engine::GetInstance().SetActiveScene(play_again ? "game_scene" : "menu_scene");
  }

 private:
  std::shared_ptr<UiText> score_text_;
  std::shared_ptr<UiButton> play_again_button_;
  std::shared_ptr<UiButton> exit_to_menu_button_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_GAME_OVER_SLIME_SHOOTER_SRC_UI_GAME_OVER_GAME_OVER_POPUP_H_
