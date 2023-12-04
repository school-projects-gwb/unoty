#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_EXPERIENCE_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_EXPERIENCE_H_

#include "entities/game_object.h"
#include "entities/behaviour_script.h"
#include "statistics/statistics.h"
#include "upgrades/upgrade_handler/upgrade_handler.h"
#include "ui/popup/popup.h"
using namespace engine::entities;

namespace slime_shooter {

class PlayerExperience : public BehaviourScript {
 public:
  void GainExperience(int amount_to_gain) {
    int current_xp = player_statistics_->GetInt(StatisticType::Experience);
    int max_xp = player_statistics_->GetInt(StatisticType::MaxExperience);

    if (current_xp + amount_to_gain >= max_xp) { // Level up
      player_statistics_->Append(StatisticType::Level, 1);
      auto leftover_xp = max_xp - (current_xp+amount_to_gain);
      player_statistics_->Set(StatisticType::Experience, leftover_xp);
      player_statistics_->Set(StatisticType::MaxExperience, max_xp * 1.05f);

      upgrade_handler_->Show();
    } else {
      player_statistics_->Set(StatisticType::Experience, current_xp + amount_to_gain);
    }
  }

 private:
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<UpgradeHandler> upgrade_handler_;
  bool is_turret_unlocked_ = false;

  void OnStart() override {
    auto player = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player->GetComponentByType<Statistics>();
    upgrade_handler_ = GameObject::Cast<UpgradeHandler>(GameObject::GetSceneObjectByName("upgrade_handler"));
  }

  void OnUpdate() override {
    if (!is_turret_unlocked_ && player_statistics_->GetInt(StatisticType::Level) == 2) {
      PopupConfig popup_config;
      popup_config.content_position_ = {engine::EngineConfig::window_width/2 - 235, 335};

      auto popup = GameObject::Cast<Popup>(GameObject::GetSceneObjectByName("popup"));
      popup->Show("NEW UNLOCK!", "Turret that shoots at enemies.", popup_config);
      GameObject::GetSceneObjectByName("player_turret", true)->SetIsActive(true);
      is_turret_unlocked_ = true;
    }
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_EXPERIENCE_H_
