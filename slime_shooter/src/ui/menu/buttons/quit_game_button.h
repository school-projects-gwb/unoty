#ifndef SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_QUIT_GAME_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_QUIT_GAME_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"

using namespace engine::entities;

namespace slime_shooter  {

class QuitGameButton : public GameObject {
 public:
  QuitGameButton() {
    auto button = GameObject::Create<UiButton>(TriggerQuitGame);
    button->SetText("QUIT GAME", GameFont::Default, 16, GameColor::Ui::TextRed);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({100, 590});
    button->SetRelativeTextPosition({80, 25});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerQuitGame() {
    engine::Engine::GetInstance().Stop();
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_QUIT_GAME_BUTTON_H_
