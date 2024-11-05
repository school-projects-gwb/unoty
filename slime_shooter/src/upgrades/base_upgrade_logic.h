#ifndef SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_LOGIC_H_
#define SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_LOGIC_H_

#include "entities/behaviour_script.h"

using namespace engine::entities;

namespace slime_shooter {

class BaseUpgradeLogic : public BehaviourScript {
 public:
  BaseUpgradeLogic(statistic_upgrades::StatisticUpgrade upgrade, std::shared_ptr<Sprite> base_upgrade_frame,
                   std::shared_ptr<Sprite> base_upgrade_symbol) :
                   upgrade_(upgrade), base_upgrade_symbol_(base_upgrade_symbol),
                   base_upgrade_frame_(base_upgrade_frame) {}

  void OnStart() override {
    auto player = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player->GetComponentByType<Statistics>();
    player_transform_ = player->GetTransform();
    current_player_level_ = player_statistics_->GetInt(StatisticType::Level);

    base_upgrade_symbol_->SetColor({255, 0, 0});
    base_upgrade_frame_->SetColor({255, 0, 0});

    transform_ = GetGameObject().GetTransform();

    pickup_sound_ = GetGameObject().GetComponentByType<AudioSource>();
  }

  void OnUpdate() override {
    HandleEnableUpgradeCheck();
    HandleApplyUpgradeCollisionCheck();
  }

 private:
  engine::utility::Timer timer_;
  int current_player_level_ = 1;
  bool is_active_ = false;
  const statistic_upgrades::StatisticUpgrade upgrade_;
  std::shared_ptr<Sprite> base_upgrade_symbol_;
  std::shared_ptr<Sprite> base_upgrade_frame_;
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<Transform> player_transform_;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<AudioSource> pickup_sound_;
  Vector2d bounds_offset_ = {0, 0};

  void HandleEnableUpgradeCheck() {
    if (current_player_level_ == player_statistics_->GetInt(StatisticType::Level) || is_active_) return;

    is_active_ = true;
    base_upgrade_symbol_->SetColor({255, 255, 255});
    base_upgrade_frame_->SetColor({255, 255, 255});
  }

  void HandleApplyUpgradeCollisionCheck() {
    if (!timer_.HasElapsed(.1) || !is_active_) return;

    auto offset_position = Vector2d{player_transform_->Position.x + bounds_offset_.x, player_transform_->Position.y + bounds_offset_.y};
    bool is_player_on_upgrade = transform_->IsInPositionBounds(offset_position);

    timer_.Start();
    if (!is_player_on_upgrade) return;

    ApplyUpgrade();
  }

  void ApplyUpgrade() {
    if (upgrade_.statistic_type == StatisticType::Health &&
    player_statistics_->GetInt(StatisticType::Health) >= player_statistics_->GetInt(StatisticType::MaxHealth)) return;

    player_statistics_->ApplyUpgrade(upgrade_);
    pickup_sound_->Play();

    base_upgrade_symbol_->SetColor({255, 0, 0});
    base_upgrade_frame_->SetColor({255, 0, 0});

    is_active_ = false;
    current_player_level_ = player_statistics_->GetInt(StatisticType::Level);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_LOGIC_H_
