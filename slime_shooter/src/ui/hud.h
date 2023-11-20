#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HUD_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HUD_H_

#include "engine/engine_config.h"
#include "hud/experience_bar/experience_bar.h"
#include "hud/health_bar/health_bar.h"
#include "score_text.h"

using namespace engine::entities;

namespace slime_shooter  {

class Hud : public UiObject {
 public:
  Hud() {
    SetLayer(2);
    GetTransform()->SetSize({engine::EngineConfig::window_width, 60});
    GetTransform()->Position = {0, 0};
    SetBackgroundColor({2, 8,17});

    auto experience_bar = GameObject::Create<ExperienceBar>();
    AddChildObject(experience_bar);

    auto health_bar = GameObject::Create<HealthBar>();
    AddChildObject(health_bar);

    auto score_text = GameObject::Create<ScoreText>();
    AddChildObject(score_text);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HUD_H_
