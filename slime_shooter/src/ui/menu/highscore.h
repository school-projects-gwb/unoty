#ifndef SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_HIGHSCORE_H_
#define SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_HIGHSCORE_H_

#include "entities/game_object.h"

using namespace engine::entities;

namespace slime_shooter {

class Highscore : public GameObject {
 public:
  Highscore() {
    auto highscore_label_text = GameObject::Create<UiText>();
    highscore_label_text->SetContent("HIGHSCORE:");
    highscore_label_text->GetTransform()->Position = {925, 100};
    highscore_label_text->SetFont(GameFont::Default, 18);
    highscore_label_text->SetColor(GameColor::Ui::TextRed);

    auto highscore_label_value = GameObject::Create<UiText>();
    highscore_label_value->SetContent("42069");
    highscore_label_value->GetTransform()->Position = {1125, 100};
    highscore_label_value->SetFont(GameFont::Default, 18);
    highscore_label_value->SetColor(GameColor::Ui::TextWhite);

    auto highscore_reset_button = GameObject::Create<UiButton>(TriggerResetHighscore);
    highscore_reset_button->SetText("RESET", GameFont::Default, 12, GameColor::Ui::SecondaryButtonText);
    highscore_reset_button->SetPosition({925, 145});
    highscore_reset_button->SetBackgroundColor(GameColor::Ui::BackgroundDark);
    highscore_reset_button->SetSize({60, 13});
    highscore_reset_button->SetTagName("button");

    AddChildObject(highscore_label_text);
    AddChildObject(highscore_label_value);
    AddChildObject(highscore_reset_button);
  }

  static void TriggerResetHighscore() {
    engine::helpers::Debug::Log("Button trigger: reset highscore");
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_HIGHSCORE_H_
