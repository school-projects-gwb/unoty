#ifndef SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_LOGO_H_
#define SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_LOGO_H_

#include "entities/ui/ui_object.h"
#include "engine/engine_config.h"

using namespace engine::entities;

namespace slime_shooter {

class HealthBarLogo : public UiObject {
 public:
  HealthBarLogo() {
    GetTransform()->Position = {0, -8};
    GetTransform()->SetScale(0.75);
    SetSpritePath("resources/sprites/ui/hp.png");
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_LOGO_H_
