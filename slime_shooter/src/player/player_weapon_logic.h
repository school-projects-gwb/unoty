#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_

#include <unordered_map>
#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/animator.h"
#include "entities/structs/input.h"
#include "entities/structs/vector.h"
#include "statistics/statistics.h"

using namespace engine::entities;

namespace slime_shooter {

class PlayerWeaponLogic : public BehaviourScript {
 public:
  void OnStart() override {
    transform_ = GetGameObject().GetTransform();
    parent_transform_ = GetGameObject().GetParent()->GetTransform();
  }

  void OnUpdate() override {
    transform_->Position = {
        parent_transform_->Position.x + position_offset.x,
        parent_transform_->Position.y + position_offset.y
    };
  }

 private:
  Point position_offset = {12, 65};
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Transform> parent_transform_;
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_
