#ifndef SLIME_SHOOTER_SRC_UI_HUD_GOD_MODE_INDICATOR_GOD_MODE_INDICATOR_H
#define SLIME_SHOOTER_SRC_UI_HUD_GOD_MODE_INDICATOR_GOD_MODE_INDICATOR_H

#include "engine/engine_config.h"
#include "entities/ui/ui_text.h"
#include "common/definitions.h"

using namespace engine::entities;

namespace slime_shooter {

class GodModeIndicator : public UiText {
 public:
  GodModeIndicator() {
    GetTransform()->Position = {10, engine::EngineConfig::window_height - 25};
    GetTransform()->SetScale(0.75);
    SetColor(GameColor::Green::Shade4);
    SetContent("Godmode enabled");
    SetFont(GameFont::Default, 14);
    SetName("god_mode_indicator_text");
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_HUD_GOD_MODE_INDICATOR_GOD_MODE_INDICATOR_H
