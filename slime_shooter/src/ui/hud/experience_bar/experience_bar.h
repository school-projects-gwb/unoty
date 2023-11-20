#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_H_

#include "entities/ui/ui_object.h"
#include "experience_bar_logo.h"
#include "experience_bar_fill.h"
#include "experience_bar_text.h"
#include "ui/hud/bar_frame.h"
#include "experience_bar_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class ExperienceBar : public UiObject {
 public:
  ExperienceBar() {
    auto experience_bar_fill = GameObject::Create<ExperienceBarFill>();
    experience_bar_fill->SetName("experience_bar_fill");
    AddChildObject(experience_bar_fill);

    auto bar_frame = GameObject::Create<BarFrame>();
    bar_frame->GetTransform()->Position = {engine::EngineConfig::window_width - 375, -120};
    AddChildObject(bar_frame);

    auto experience_bar_logo = GameObject::Create<ExperienceBarLogo>();
    AddChildObject(experience_bar_logo);

    auto experience_bar_text = GameObject::Create<ExperienceBarText>();
    experience_bar_text->SetName("experience_bar_text");
    AddChildObject(experience_bar_text);

    auto experience_bar_logic = Component::Create<ExperienceBarLogic>();
    AddComponent(experience_bar_logic);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_H_
