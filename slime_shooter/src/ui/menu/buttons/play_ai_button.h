#ifndef SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_PLAY_AI_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_PLAY_AI_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"

using namespace engine::entities;

namespace slime_shooter  {

class PlayAiButton : public GameObject {
 public:
  PlayAiButton() {
    auto button = GameObject::Create<UiButton>(TriggerPlayAiTest);
    button->SetText("AI TEST", GameFont::Default, 12, GameColor::Ui::TextWhite);
    button->SetBackgroundColor(GameColor::Purple::Shade1);
    button->SetSize({185, 25});
    button->SetPosition({450, 590});
    button->SetRelativeTextPosition({50, 7});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerPlayAiTest() {
    engine::Engine::GetInstance().SetActiveScene("ai_demo_scene");
  };
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_SLIME_SHOOTER_SRC_UI_MENU_BUTTONS_PLAY_AI_BUTTON_H_
