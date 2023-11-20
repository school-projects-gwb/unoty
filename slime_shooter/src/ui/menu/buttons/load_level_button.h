#ifndef SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LOAD_LEVEL_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LOAD_LEVEL_BUTTON_H_

#include "engine/engine_config.h"
#include "ui/hud/score/score_text.h"
#include "entities/ui/ui_button.h"
#include "iostream"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"

using namespace engine::entities;

namespace slime_shooter  {

class LoadLevelButton : public GameObject {
 public:
  LoadLevelButton() {
    auto button = GameObject::Create<UiButton>(TriggerLoadLevel);
    button->SetText("LOAD LEVEL", GameFont::Default, 18, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({100, 325});
    button->SetRelativeTextPosition({60, 20});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerLoadLevel() {
    engine::helpers::Debug::Log("Button trigger: Load level");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LOAD_LEVEL_BUTTON_H_
