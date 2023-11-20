#ifndef SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_FILL_H_
#define SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_FILL_H_

#include "entities/ui/ui_object.h"
#include "engine/engine_config.h"

using namespace engine::entities;

namespace slime_shooter {

class HealthBarFill : public UiObject {
 public:
  HealthBarFill() {
    GetTransform()->Position = {50, 17};
    GetTransform()->SetSize({210, 27});
    SetBackgroundColor(GameColor::Coral::Shade1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_FILL_H_
