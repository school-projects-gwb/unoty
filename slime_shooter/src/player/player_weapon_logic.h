#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/structs/input.h"
#include "entities/structs/vector_2d.h"

using namespace engine::entities;

namespace slime_shooter {

class PlayerWeaponLogic : public BehaviourScript {
 public:
  void OnStart() override {
    transform_ = GetGameObject().GetTransform();
    parent_transform_ = GetGameObject().GetParent()->GetTransform();
    weapon_sprite_ = GetGameObject().GetComponentByType<Sprite>();
  }

  void OnUpdate() override {
    transform_->Position = {
        parent_transform_->Position.x + position_offset_.x,
        parent_transform_->Position.y + position_offset_.y
    };
  }

  void SetCanShoot(bool can_shoot) {
    can_shoot_ = can_shoot;
    weapon_sprite_->SetColor(can_shoot_ ? Color{255, 255, 255} : Color{255, 0, 0});
  }

 private:
  bool can_shoot_ = true;
  Point position_offset_ = {12, 65};
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Transform> parent_transform_;
  std::shared_ptr<Sprite> weapon_sprite_;
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_
