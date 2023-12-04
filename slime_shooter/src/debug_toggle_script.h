#ifndef SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_
#define SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_

#include "engine/engine.h"
#include "iostream"
#include "entities/listeners/key_listener.h"
#include "player/player_experience.h"
#include "player/player_health.h"

using namespace engine::entities;

namespace slime_shooter {

class DebugToggleScript : public KeyListener {
 private:
  bool is_player_initialised_ = false;
  std::shared_ptr<GameObject> player_;
  std::shared_ptr<Statistics> player_statistics_;

  void OnKeyPressed() override {
    if (!is_player_initialised_) InitPlayer();
    if (Input::HasPressedKey(Key::UnoZ))
      engine::Engine::GetInstance().ToggleDebugMode();

    if (Input::HasPressedKey(Key::UnoP))
      engine::Engine::GetInstance().SetActiveScene("menu_scene");
    
    if (Input::HasPressedKey(Key::UnoL))
      engine::EngineConfig::is_paused = !engine::EngineConfig::is_paused;

    // Player Level
    if (Input::HasPressedKey(Key::Uno1)) {
      auto current_xp = player_statistics_->GetInt(StatisticType::Experience);
      auto max_xp = player_statistics_->GetInt(StatisticType::MaxExperience);
      player_->GetComponentByType<PlayerExperience>()->GainExperience(max_xp - current_xp);
    }

    // Player Experience
    if (Input::HasPressedKey(Key::Uno2))
      player_->GetComponentByType<PlayerExperience>()->GainExperience(1);

    // GAIN Player Health
    if (Input::HasPressedKey(Key::Uno3)) {
      int health = player_statistics_->GetInt(StatisticType::Health);
      if (health < player_statistics_->GetInt(StatisticType::MaxHealth)) player_statistics_->Set(StatisticType::Health, health+1);
    }

    // LOSE Player Health
    if (Input::HasPressedKey(Key::Uno4)) {
      player_->GetComponentByType<PlayerHealth>()->TakeDamage(1);
    }
  }

  void InitPlayer() {
    player_ = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player_->GetComponentByType<Statistics>();
  }
};

}

#endif //SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_
