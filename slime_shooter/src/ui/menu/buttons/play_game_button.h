#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_TEST_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_TEST_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"

using namespace engine::entities;

namespace slime_shooter  {

class PlayGameButton : public GameObject {
 public:
  PlayGameButton() {
    auto button = GameObject::Create<UiButton>(TriggerPlayGame);
    button->SetText("PLAY GAME", GameFont::Default, 24, GameColor::Ui::PrimaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::PrimaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({100, 185});
    button->SetRelativeTextPosition({45, 20});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerPlayGame() {
    engine::Engine::GetInstance().SetActiveScene("game_scene");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_TEST_BUTTON_H_
