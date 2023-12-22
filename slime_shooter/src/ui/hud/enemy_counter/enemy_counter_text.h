#ifndef SLIME_SHOOTER_SRC_UI_HUD_ENEMY_COUNTER_ENEMY_COUNTER_TEXT_H
#define SLIME_SHOOTER_SRC_UI_HUD_ENEMY_COUNTER_ENEMY_COUNTER_TEXT_H

#include "engine/engine_config.h"
#include "entities/ui/ui_text.h"
#include "common/definitions.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemyCounterText : public UiText {
 public:
  EnemyCounterText() {
    GetTransform()->Position = {15, 125};
    GetTransform()->SetScale(0.75);
    SetColor(GameColor::Green::Shade4);

    SetContent("Pool size: 0, Alive: 0");
    SetFont(GameFont::Default, 16);
    SetName("enemy_counter_text");
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_HUD_ENEMY_COUNTER_ENEMY_COUNTER_TEXT_H
