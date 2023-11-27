#ifndef SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_LEVEL_PREVIOUS_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_LEVEL_PREVIOUS_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"

using namespace engine::entities;

namespace slime_shooter  {

class LevelPreviousButton : public GameObject {
 public:
  LevelPreviousButton(std::function<void(bool)> callback) {
    set_next_callback_ = callback;

    auto button = GameObject::Create<UiButton>(TriggerSwitchLevel);
    button->SetText("<", GameFont::Default, 18, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetPosition(Vector2d{475, 200});
    button->SetSize({30, 30});
    button->SetRelativeTextPosition({7, 7});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerSwitchLevel() {
    set_next_callback_(false);
  };

 private:
  static inline std::function<void(bool)> set_next_callback_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_LEVEL_PREVIOUS_BUTTON_H_
