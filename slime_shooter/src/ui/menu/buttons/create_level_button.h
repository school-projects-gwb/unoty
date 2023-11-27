#ifndef SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LEVEL_EDITOR_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LEVEL_EDITOR_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"
#include "config/level_editor_config.h"

using namespace engine::entities;

namespace slime_shooter  {

class CreateLevelButton : public GameObject {
 public:
  CreateLevelButton() {
    auto button = GameObject::Create<UiButton>(TriggerLevelEditor);
    button->SetText("CREATE NEW LEVEL", GameFont::Default, 16, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({100, 325});
    button->SetRelativeTextPosition({25, 25});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerLevelEditor() {
    LevelEditorConfig::EnableEditor(true);
    engine::Engine::GetInstance().SetActiveScene("level_editor_scene");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LEVEL_EDITOR_BUTTON_H_
