#ifndef SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_DELETE_LEVEL_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_DELETE_LEVEL_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"
#include "config/level_editor_config.h"

using namespace engine::entities;

namespace slime_shooter  {

class DeleteLevelButton : public GameObject {
 public:
  DeleteLevelButton() {
    auto button = GameObject::Create<UiButton>(TriggerDeleteLevel);
    button->SetText("DELETE LEVEL", GameFont::Default, 14, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({100, 485});
    button->SetRelativeTextPosition({70, 25});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerDeleteLevel() {
    LevelEditorConfig::DeleteCurrentActiveLevel();
    engine::Engine::GetInstance().SetActiveScene("menu_scene");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_DELETE_LEVEL_BUTTON_H_
