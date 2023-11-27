#ifndef SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_BUTTONS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_BUTTONS_BACK_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_BUTTONS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_BUTTONS_BACK_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"

using namespace engine::entities;

namespace slime_shooter  {

class BackButton : public GameObject {
 public:
  BackButton() {
    auto button = GameObject::Create<UiButton>(TriggerLoadLevel);
    button->SetText("BACK TO MENU", GameFont::Default, 18, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({350, 600});
    button->SetRelativeTextPosition({45, 20});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerLoadLevel() {
    engine::Engine::GetInstance().SetActiveScene("menu_scene");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_BUTTONS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_BUTTONS_BACK_BUTTON_H_
