#ifndef SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_LOGO_H_
#define SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_LOGO_H_

#include "entities/ui/ui_object.h"
#include "engine/engine_config.h"

using namespace engine::entities;

namespace slime_shooter {

class ExperienceBarLogo : public UiObject {
 public:
  ExperienceBarLogo() {
    GetTransform()->Position = {engine::EngineConfig::window_width - 375, -8};
    GetTransform()->SetScale(0.75);
    SetSpritePath("resources/sprites/ui/xp.png");
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_LOGO_H_
