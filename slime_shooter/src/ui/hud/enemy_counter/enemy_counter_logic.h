#ifndef SLIME_SHOOTER_SRC_UI_HUD_ENEMY_COUNTER_H
#define SLIME_SHOOTER_SRC_UI_HUD_ENEMY_COUNTER_H

#include "entities/behaviour_script.h"
#include "statistics/statistics.h"
#include "enemy_counter_text.h"
#include "enemies/enemy_object_pool.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemyCounterLogic : public BehaviourScript {
 public:
  void OnStart() override {
    auto counter_text_gameobject = GameObject::GetSceneObjectByName("enemy_counter_text", true);
    counter_text_ = GameObject::Cast<EnemyCounterText>(counter_text_gameobject);

    auto viewport_rendering_text_gameobject = GameObject::GetSceneObjectByName("viewport_rendering_text", true);
    viewport_rendering_text_ = GameObject::Cast<UiText>(viewport_rendering_text_gameobject);
  }

  void OnUpdate() override {
    counter_text_->SetContent("Pool size: " + std::to_string(StressTestConfig::enemy_pool_size) + ", Alive: " + std::to_string(StressTestConfig::alive_enemies));
    std::string text = "Render objects outside of viewport: ";
    text += StressTestConfig::viewport_rendering_enabled ? "false" : "true";
    viewport_rendering_text_->SetContent(text);
  }

 private:
  std::shared_ptr<EnemyCounterText> counter_text_;
  std::shared_ptr<UiText> viewport_rendering_text_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_HUD_ENEMY_COUNTER_H
