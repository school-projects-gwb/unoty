#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HUD_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HUD_H_

#include "engine/engine_config.h"
#include "ui/hud/experience_bar/experience_bar.h"
#include "ui/hud/health_bar/health_bar.h"
#include "ui/hud/score/score_text.h"
#include "ui/hud/score/score_logic.h"
#include "ui/hud/enemy_counter/enemy_counter_logic.h"
#include "ui/hud/god_mode_indicator/god_mode_indicator.h"
#include "ui/hud/god_mode_indicator/god_mode_indicator_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class Hud : public UiObject {
 public:
  explicit Hud(bool show_enemy_count = false) {
    SetLayer(2);
    GetTransform()->SetSize({engine::EngineConfig::window_width, 60});
    GetTransform()->Position = {0, 0};
    SetBackgroundColor({2, 8, 17});

    auto experience_bar = GameObject::Create<ExperienceBar>();
    AddChildObject(experience_bar);

    auto health_bar = GameObject::Create<HealthBar>();
    AddChildObject(health_bar);

    auto score_text = GameObject::Create<ScoreText>();
    AddChildObject(score_text);

    auto score_logic = GameObject::Create<ScoreLogic>();
    AddComponent(score_logic);

    auto god_mode_text = GameObject::Create<GodModeIndicator>();
    AddChildObject(god_mode_text);

    auto god_mode_indicator = GameObject::Create<GodModeIndicatorLogic>();
    AddComponent(god_mode_indicator);

    if (show_enemy_count) {
      auto stress_test_debug_text = GameObject::Create<UiText>();

      stress_test_debug_text->GetTransform()->Position = {15, 75};
      stress_test_debug_text->GetTransform()->SetScale(0.75);
      stress_test_debug_text->SetColor(GameColor::Green::Shade4);
      stress_test_debug_text->SetContent("Press (1) to increase enemy pool size, press (2) to toggle viewport rendering");
      stress_test_debug_text->SetFont(GameFont::Default, 14);
      stress_test_debug_text->SetName("stress_test_debug_text");

      AddChildObject(stress_test_debug_text);

      auto viewport_rendering_text = GameObject::Create<UiText>();

      viewport_rendering_text->GetTransform()->Position = {15, 175};
      viewport_rendering_text->GetTransform()->SetScale(0.75);
      viewport_rendering_text->SetColor(GameColor::Green::Shade4);
      viewport_rendering_text->SetContent("Render objects outside of viewport: true");
      viewport_rendering_text->SetFont(GameFont::Default, 16);
      viewport_rendering_text->SetName("viewport_rendering_text");

      AddChildObject(viewport_rendering_text);

      auto enemy_counter_text = GameObject::Create<EnemyCounterText>();
      AddChildObject(enemy_counter_text);

      auto enemy_counter = GameObject::Create<EnemyCounterLogic>();
      AddComponent(enemy_counter);
    }
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_HUD_H_
