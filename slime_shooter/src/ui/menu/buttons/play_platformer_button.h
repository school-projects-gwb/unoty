#ifndef SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_PLAY_PLATFORMER_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_PLAY_PLATFORMER_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"

using namespace engine::entities;

namespace slime_shooter  {

class PlayPlatformerButton : public GameObject {
 public:
  PlayPlatformerButton() {
    auto button = GameObject::Create<UiButton>(TriggerPlayStressTest);
    button->SetText("PLATFORMER", GameFont::Default, 12, GameColor::Ui::TextWhite);
    button->SetBackgroundColor(GameColor::Purple::Shade1);
    button->SetSize({185, 25});
    button->SetPosition({645, 623});
    button->SetRelativeTextPosition({30, 7});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerPlayStressTest() {
    engine::Engine::GetInstance().SetActiveScene("platformer_scene");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_PLAY_PLATFORMER_BUTTON_H_
