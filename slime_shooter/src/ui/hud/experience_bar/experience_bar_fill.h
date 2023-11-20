#ifndef SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_FILL_H_
#define SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_FILL_H_

#include "entities/ui/ui_object.h"
#include "engine/engine_config.h"
#include "common/definitions.h"

using namespace engine::entities;

namespace slime_shooter {

class ExperienceBarFill : public UiObject {
 public:
  ExperienceBarFill() {
    GetTransform()->Position = {engine::EngineConfig::window_width - 325, 17};
    GetTransform()->SetSize({210, 27});
    SetBackgroundColor(GameColor::Green::Shade4);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_FILL_H_
