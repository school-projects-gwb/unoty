#ifndef SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_TEXT_H_
#define SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_TEXT_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_text.h"

using namespace engine::entities;

namespace slime_shooter {

class HealthBarText : public UiText {
 public:
  HealthBarText() {
    GetTransform()->Position = {275, 25};
    GetTransform()->SetScale(0.75);
    SetColor(GameColor::Coral::Shade1);
    SetContent("5/5");
    SetFont(GameFont::Default);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_TEXT_H_
