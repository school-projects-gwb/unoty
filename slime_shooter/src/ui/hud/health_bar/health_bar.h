#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_H_

#include "entities/ui/ui_object.h"
#include "health_bar_logo.h"
#include "health_bar_fill.h"
#include "health_bar_text.h"
#include "ui/hud/bar_frame.h"
#include "health_bar_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class HealthBar : public UiObject, public BehaviourScript {
 public:
  HealthBar() {
    auto health_bar_fill = GameObject::Create<HealthBarFill>();
    health_bar_fill->SetName("health_bar_fill");
    AddChildObject(health_bar_fill);

    auto bar_frame = GameObject::Create<BarFrame>();
    bar_frame->GetTransform()->Position = {0, -120};
    AddChildObject(bar_frame);

    auto health_bar_logo = GameObject::Create<HealthBarLogo>();
    AddChildObject(health_bar_logo);

    auto health_bar_text = GameObject::Create<HealthBarText>();
    health_bar_text->SetName("health_bar_text");
    AddChildObject(health_bar_text);

    auto health_bar_logic = Component::Create<HealthBarLogic>();
    AddComponent(health_bar_logic);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_H_
