#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_HEALTH_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_HEALTH_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "statistics/statistics.h"
#include "upgrades/upgrade_handler/upgrade_handler.h"
#include "ui/game_over/game_over_popup.h"
#include "utility/timer.h"

using namespace engine::entities;

namespace slime_shooter {

class PlayerHealth : public BehaviourScript {
 public:
  void TakeDamage(int damage_amount) {
    int current_health = player_statistics_->GetInt(StatisticType::Health);
    damage_taken_sound_->Play();

    if (current_health - damage_amount <= 0) {
      player_statistics_->Set(StatisticType::Health, 0);
      GetGameObject().GetComponentByType<PlayerMovement>()->StopWalkSound(); // Stop walking sound in case player was walking while dying
      game_over_popup_->Show();
    } else {
      player_statistics_->Append(StatisticType::Health, static_cast<float>(-damage_amount));
    }

    damage_cooldown_timer_.Start();
  }

 private:
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<GameOverPopup> game_over_popup_;
  std::shared_ptr<AudioSource> damage_taken_sound_;

  double damage_cooldown_seconds_ = 1;
  engine::utility::Timer damage_cooldown_timer_;

  void OnStart() override {
    player_statistics_ = GetGameObject().GetComponentByType<Statistics>();
    damage_taken_sound_ = GetGameObject().GetComponentByType<AudioSource>();
    game_over_popup_ = GameObject::Cast<GameOverPopup>(GameObject::GetSceneObjectByName("game_over_popup"));

    damage_taken_sound_ = Component::Create<AudioSource>("resources/audio/damage_taken.wav");
    damage_taken_sound_->SetVolume(10);
    GetGameObject().AddComponent(damage_taken_sound_);
  }

  void OnCollisionEnter(engine::entities::GameObject *&colliding_object) override {
    if (colliding_object->GetTagName() != "Enemy") return;

    if (damage_cooldown_timer_.HasElapsed(damage_cooldown_seconds_))
      TakeDamage(engine::EngineConfig::player_god_mode ? 0 : 1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_HEALTH_H_
