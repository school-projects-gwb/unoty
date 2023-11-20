#ifndef SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_GHOST_ENEMY_H_
#define SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_GHOST_ENEMY_H_

#include "entities/game_object.h"
#include "string"
#include "entities/animator.h"
#include "statistics/statistics.h"
#include "enemies/enemy_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class GhostEnemy : public GameObject {
 public:
  GhostEnemy() {
    auto animator = Component::Create<Animator>("resources/sprites/enemies/ghost.png",
                                                4, Point{16, 16}, Point{2, 2});

    auto enemy_logic = Component::Create<EnemyLogic>();

    AddComponent(animator);
    AddComponent(enemy_logic);

    GetTransform()->SetSize({75, 75});
    SetLayer(1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_GHOST_ENEMY_H_
