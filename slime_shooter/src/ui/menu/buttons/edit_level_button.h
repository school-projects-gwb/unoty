#ifndef SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LOAD_LEVEL_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LOAD_LEVEL_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"
#include "config/level_editor_config.h"

using namespace engine::entities;

namespace slime_shooter  {

class EditLevelButton : public GameObject {
 public:
  EditLevelButton() {
    auto button = GameObject::Create<UiButton>(TriggerEditLevel);
    button->SetText("EDIT LEVEL", GameFont::Default, 16, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({100, 405});
    button->SetRelativeTextPosition({75, 25});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerEditLevel() {
    LevelEditorConfig::EnableEditor(false);
    engine::Engine::GetInstance().SetActiveScene("level_editor_scene");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_BUTTONS_SLIME_SHOOTER_SRC_UI_BUTTONS_LOAD_LEVEL_BUTTON_H_
