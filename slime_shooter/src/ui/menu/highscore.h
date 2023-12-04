#ifndef SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_HIGHSCORE_H_
#define SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_HIGHSCORE_H_

#include "entities/game_object.h"

using namespace engine::entities;

namespace slime_shooter {

class Highscore : public GameObject {
 public:
  Highscore() {
    auto high_score_label_text = GameObject::Create<UiText>();
    high_score_label_text->SetContent("HIGHSCORE:");
    high_score_label_text->GetTransform()->Position = {925, 100};
    high_score_label_text->SetFont(GameFont::Default, 18);
    high_score_label_text->SetColor(GameColor::Ui::TextRed);

    high_score_label_value_ = GameObject::Create<UiText>();
    high_score_label_value_->SetContent(GameConfig::GetPropertyValue("high_score"));
    high_score_label_value_->GetTransform()->Position = {1125, 100};
    high_score_label_value_->SetFont(GameFont::Default, 18);
    high_score_label_value_->SetColor(GameColor::Ui::TextWhite);

    auto high_score_reset_button = GameObject::Create<UiButton>(TriggerResetHighscore);
    high_score_reset_button->SetText("RESET", GameFont::Default, 12, GameColor::Ui::SecondaryButtonText);
    high_score_reset_button->SetPosition({925, 145});
    high_score_reset_button->SetBackgroundColor(GameColor::Ui::BackgroundDark);
    high_score_reset_button->SetSize({60, 13});
    high_score_reset_button->SetTagName("button");

    AddChildObject(high_score_label_text);
    AddChildObject(high_score_label_value_);
    AddChildObject(high_score_reset_button);
  }

 private:
  static inline std::shared_ptr<UiText> high_score_label_value_;

  static void TriggerResetHighscore() {
    GameConfig::SetPropertyValue("high_score", "0");
    high_score_label_value_->SetContent("0");
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_HIGHSCORE_H_
