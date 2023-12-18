#ifndef SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ENEMY_BASE_H_
#define SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ENEMY_BASE_H_

#include "entities/game_object.h"
#include "string"
#include "enemies/enemy_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemyBase : public GameObject {
 public:
  EnemyBase() {
    enemy_logic_ = Component::Create<EnemyLogic>();
    AddComponent(enemy_logic_);

    SetLayer(2);
    SetTagName("Enemy");
  }

  void TakeDamage(bool is_from_turret) {
    enemy_logic_->TakeDamage(is_from_turret);
  }

  bool HasDied() {
    return enemy_logic_->HasDied();
  }

 private:
  std::shared_ptr<EnemyLogic> enemy_logic_;
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ENEMY_BASE_H_
