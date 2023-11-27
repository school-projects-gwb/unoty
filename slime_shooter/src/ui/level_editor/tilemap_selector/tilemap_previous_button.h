#ifndef SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_TILEMAP_PREVIOUS_BUTTON_H_
#define SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_TILEMAP_PREVIOUS_BUTTON_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "engine/engine.h"
#include "utility/debug.h"

using namespace engine::entities;

namespace slime_shooter  {

class TilemapPreviousButton : public GameObject {
 public:
  TilemapPreviousButton(std::function<void(bool)> callback) {
    set_next_callback_ = callback;

    auto button = GameObject::Create<UiButton>(TriggerSetTileMap);
    button->SetText("<", GameFont::Default, 18, GameColor::Ui::SecondaryButtonText);
    button->SetBackgroundColor(GameColor::Ui::SecondaryButtonBackground);
    button->SetPosition(Vector2d{760, 80});
    button->SetSize({30, 30});
    button->SetRelativeTextPosition({7, 7});
    button->SetTagName("button");

    AddChildObject(button);
  }

  static void TriggerSetTileMap() {
    set_next_callback_(false);
  };

 private:
  static inline std::function<void(bool)> set_next_callback_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_TILEMAP_PREVIOUS_BUTTON_H_
