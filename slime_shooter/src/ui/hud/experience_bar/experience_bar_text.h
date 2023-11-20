#ifndef SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_TEXT_H_
#define SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_TEXT_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_text.h"

using namespace engine::entities;

namespace slime_shooter {

class ExperienceBarText : public UiText {
 public:
  ExperienceBarText() {
    GetTransform()->Position = {engine::EngineConfig::window_width - 100, 25};
    GetTransform()->SetScale(0.75);
    SetColor(GameColor::Green::Shade4);
    SetContent("LVL. 1");
    SetFont(GameFont::Default);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_TEXT_H_
