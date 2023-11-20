#ifndef SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ORANGE_SLIME_ENEMY_H_
#define SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ORANGE_SLIME_ENEMY_H_

#include "entities/game_object.h"
#include "string"
#include "entities/animator.h"
#include "statistics/statistics.h"
#include "enemies/enemy_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class OrangeSlimeEnemy : public GameObject {
 public:
  OrangeSlimeEnemy() {
    auto animator = Component::Create<Animator>("resources/sprites/enemies/slime_orange.png",
                                                4, Point{16, 16}, Point{2, 2});
    animator->SetSpriteSheetAtIndex("resources/sprites/enemies/slime_orange.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->Play(true);

    auto enemy_logic = Component::Create<EnemyLogic>();

    AddComponent(animator);
    AddComponent(enemy_logic);

    GetTransform()->SetSize({60, 60});
    SetLayer(1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ORANGE_SLIME_ENEMY_H_
