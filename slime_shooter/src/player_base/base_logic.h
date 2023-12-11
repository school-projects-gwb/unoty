#ifndef SLIME_SHOOTER_SRC_PLAYER_BASE_SLIME_SHOOTER_SRC_PLAYER_BASE_BASE_LOGIC_H_
#define SLIME_SHOOTER_SRC_PLAYER_BASE_SLIME_SHOOTER_SRC_PLAYER_BASE_BASE_LOGIC_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "statistics/statistics.h"
#include "utility/timer.h"
#include "player/player_weapon.h"
#include "ui/popup/popup.h"

using namespace engine::entities;

namespace slime_shooter {

class BaseLogic : public BehaviourScript {
 public:
  BaseLogic() : timer_() {}

  void OnStart() override {
    auto player = GameObject::GetSceneObjectByName("Player");

    std::shared_ptr<PlayerWeapon> weapon_object = GameObject::Cast<PlayerWeapon>(GameObject::GetSceneObjectByName("PlayerWeapon", true));
    player_weapon_ = weapon_object->GetComponentByType<PlayerWeaponLogic>();

    player_statistics_ = player->GetComponentByType<Statistics>();
    player_transform_ = player->GetTransform();
    transform_ = GetGameObject().GetTransform();

    popup_ = GameObject::Cast<Popup>(GameObject::GetSceneObjectByName("popup"));
  }

  void OnUpdate() override {
    if (!can_move_outside_base_) ProcessMoveOutsideBaseCheck();

    if (!can_move_outside_base_ && player_statistics_->GetInt(StatisticType::Level) == 10) {
      PopupConfig popup_config;
      popup_config.content_position_ = {engine::EngineConfig::window_width/2 - 300, 335};

      popup_->Show("NEW UNLOCK!", "You can now shoot outside of the base.", popup_config);
      can_move_outside_base_ = true;
      player_weapon_->SetCanShoot(true);
    }
  }

 private:
  bool is_player_in_base_{};
  bool can_move_outside_base_ = false;
  engine::utility::Timer timer_;
  Vector2d bounds_offset_ = {300, 150};
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<Transform> player_transform_;
  std::shared_ptr<PlayerWeaponLogic> player_weapon_;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Popup> popup_;

  void ProcessMoveOutsideBaseCheck() {
    if (!timer_.HasElapsed(0.25)) return;

    auto offset_position = Vector2d{player_transform_->Position.x - bounds_offset_.x, player_transform_->Position.y - bounds_offset_.y};
    bool is_player_in_base = transform_->IsInPositionBounds(offset_position);

    if (is_player_in_base != is_player_in_base_) {
      player_weapon_->SetCanShoot(is_player_in_base);
      is_player_in_base_ = is_player_in_base;
    }

    timer_.Start();
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_BASE_SLIME_SHOOTER_SRC_PLAYER_BASE_BASE_LOGIC_H_
