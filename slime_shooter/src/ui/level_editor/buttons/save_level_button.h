#ifndef SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_SAVE_GAME_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_SAVE_GAME_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"

using namespace engine::entities;

namespace slime_shooter  {

class SaveLevelButton : public GameObject {
 public:
  SaveLevelButton(std::function<void()> trigger_save_level_callback) {
    trigger_save_level_callback_ = trigger_save_level_callback;

    auto button = GameObject::Create<UiButton>(TriggerSaveLevel);
    button->SetText("SAVE LEVEL", GameFont::Default, 18, GameColor::Ui::PrimaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::PrimaryButtonBackground);
    button->SetSize({300, 60});
    button->SetPosition({25, 600});
    button->SetRelativeTextPosition({65, 20});
    button->SetTagName("button");

    AddChildObject(button);
  }

 private:
  static inline std::function<void()> trigger_save_level_callback_;

  static void TriggerSaveLevel() {
    trigger_save_level_callback_();
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_SAVE_GAME_BUTTON_H_
