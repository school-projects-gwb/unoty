#ifndef SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_
#define SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_

#include "engine/engine.h"
#include "iostream"
#include "entities/listeners/key_listener.h"
#include "player/player_experience.h"
#include "player/player_health.h"
#include "enemies/enemy_object_pool.h"
#include "config/stress_test_config.h"

using namespace engine::entities;

namespace slime_shooter {

class DebugToggleScript : public KeyListener {
 private:
  bool is_player_initialised_ = false;
  std::shared_ptr<GameObject> player_;
  std::shared_ptr<Statistics> player_statistics_;

  void OnKeyPressed() override {
    auto scene_name = engine::Engine::GetInstance().GetActiveScene()->GetSceneName();

    // FPS related keyhandlers that should work in every scene

    // Increase FPS
    if (Input::HasPressedKey(Key::UnoPageUp))
      engine::Engine::GetInstance().IncrementFps();

    // Decrease FPS
    if (Input::HasPressedKey(Key::UnoPageDown))
      engine::Engine::GetInstance().DecrementFps();

    // Reset FPS
    if (Input::HasPressedKey(Key::UnoHome))
      engine::Engine::GetInstance().ResetFps();

    // Toggle god mode
    if (Input::HasPressedKey(Key::UnoX))
      engine::Engine::GetInstance().ToggleGodMode();

    // Toggle debug mode & FPS counter
    if (Input::HasPressedKey(Key::UnoZ))
      engine::Engine::GetInstance().ToggleDebugMode();

    if (scene_name == "menu_scene")
      return;

    if (!is_player_initialised_)
      InitPlayer();

    // Return to menu
    if (Input::HasPressedKey(Key::UnoP)
        || (Input::IsGamepadPluggedIn() && Input::HasPressedGamepadButton(GamepadButton::Start))) {
      engine::Engine::GetInstance().SetActiveScene("menu_scene");
      EnemyObjectPool::GetInstance().ResetPool();
    }

    // Key listeners for the Physics Stresstest scene
    if (scene_name == "stress_test_scene") {
      if (Input::HasPressedKey(Key::Uno1)) {
        EnemyObjectPool::GetInstance().IncreasePoolSize(StressTestConfig::hotkey_increase_enemy_pool_amount);
      }

      if (Input::HasPressedKey(Key::Uno2)) {
        StressTestConfig::viewport_rendering_enabled = !StressTestConfig::viewport_rendering_enabled;
        engine::Engine::GetInstance().GetActiveScene()->SetViewportRendering(StressTestConfig::viewport_rendering_enabled);
      }
    }

    // Key listeners for the regular game scene
    if (scene_name == "game_scene") {
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
        if (health < player_statistics_->GetInt(StatisticType::MaxHealth))
          player_statistics_->Set(StatisticType::Health, static_cast<float>(health) + 1);
      }

      // LOSE Player Health
      if (Input::HasPressedKey(Key::Uno4)) {
        player_->GetComponentByType<PlayerHealth>()->TakeDamage(1);
      }
    }
  }

  void InitPlayer() {
    player_ = GameObject::GetSceneObjectByName("Player");
    if (player_ == nullptr)
      return;

    player_statistics_ = player_->GetComponentByType<Statistics>();
    is_player_initialised_ = true;
  }
};

}

#endif //SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_
