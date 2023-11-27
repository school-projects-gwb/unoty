#ifndef SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_ATTACK_H_
#define SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_ATTACK_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/structs/input.h"
#include "entities/structs/vector_2d.h"

using namespace engine::entities;

namespace slime_shooter {

// TODO implement
class EnemyAttack : public BehaviourScript {
 public:
  void OnUpdate() override {
    if (!is_target_set_) SetTarget();
  }

  void StartAttack() {
    
  }

  void SetTarget() {

  }

 private:
  bool is_target_set_ = false;
  std::shared_ptr<Transform> parent_transform_;
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_ATTACK_H_
