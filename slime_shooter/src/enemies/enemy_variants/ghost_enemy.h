#ifndef SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_GHOST_ENEMY_H_
#define SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_GHOST_ENEMY_H_

#include "entities/game_object.h"
#include "string"
#include "entities/animator.h"
#include "statistics/statistics.h"
#include "enemies/enemy_logic.h"
#include "enemy_base.h"
#include "enemies/enemy_attack.h"

using namespace engine::entities;

namespace slime_shooter {

class GhostEnemy : public EnemyBase {
 public:
  GhostEnemy() : EnemyBase() {
    auto animator = Component::Create<Animator>("resources/sprites/enemies/ghost.png",
                                                4, Point{16, 16}, Point{2, 2});
    AddComponent(animator);

    auto attack = Component::Create<EnemyAttack>();
    AddComponent(attack);

    auto logic = GetComponentByType<EnemyLogic>();
    logic->SetExperienceAmount(2);

    GetTransform()->SetSize({75, 75});
  }

  static std::shared_ptr<EnemyBase> Create() {
    auto object = GameObject::Create<GhostEnemy>();
    object->SetIsActive(false);
    return object;
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_GHOST_ENEMY_H_
