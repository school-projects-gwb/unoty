#ifndef SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LEVEL_EDITOR_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LEVEL_EDITOR_BUTTON_H_

#include "engine/engine_config.h"
#include "ui/hud/score/score_text.h"
#include "entities/ui/ui_button.h"
#include "iostream"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"

using namespace engine::entities;

namespace slime_shooter  {

class LevelEditorButton : public GameObject {
 public:
  LevelEditorButton() {
    auto button = GameObject::Create<UiButton>(TriggerLevelEditor);
    button->SetText("LEVEL EDITOR", GameFont::Default, 18, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({100, 405});
    button->SetRelativeTextPosition({40, 20});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerLevelEditor() {
    engine::helpers::Debug::Log("Button trigger: Load level");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LEVEL_EDITOR_BUTTON_H_
