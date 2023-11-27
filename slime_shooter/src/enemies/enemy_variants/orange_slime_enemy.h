#ifndef SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ORANGE_SLIME_ENEMY_H_
#define SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ORANGE_SLIME_ENEMY_H_

#include "entities/game_object.h"
#include "string"
#include "entities/animator.h"
#include "statistics/statistics.h"
#include "enemies/enemy_logic.h"
#include "enemy_base.h"

using namespace engine::entities;

namespace slime_shooter {

class OrangeSlimeEnemy : public EnemyBase {
 public:
  OrangeSlimeEnemy() : EnemyBase() {
    auto animator = Component::Create<Animator>("resources/sprites/enemies/slime_orange.png",
                                                4, Point{16, 16}, Point{2, 2});
    animator->SetSpriteSheetAtIndex("resources/sprites/enemies/slime_orange.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->Play(true);

    AddComponent(animator);

    GetTransform()->SetSize({60, 60});
  }

  static std::shared_ptr<EnemyBase> Create() {
    auto object = GameObject::Create<OrangeSlimeEnemy>();
    object->SetIsActive(false);
    return object;
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_ORANGE_SLIME_ENEMY_H_
