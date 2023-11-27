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
    auto enemy_logic = Component::Create<EnemyLogic>();
    AddComponent(enemy_logic);
    SetLayer(2);
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ENEMY_BASE_H_
