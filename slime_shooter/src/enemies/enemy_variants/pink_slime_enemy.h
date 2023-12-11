#ifndef SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_PINK_SLIME_ENEMY_H_
#define SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_PINK_SLIME_ENEMY_H_

#include "entities/game_object.h"
#include "string"
#include "entities/animator.h"
#include "statistics/statistics.h"
#include "enemies/enemy_logic.h"
#include "enemy_base.h"
#include "entities/rigid_body.h"
#include "entities/colliders/box_collider.h"

using namespace engine::entities;

namespace slime_shooter {

class PinkSlimeEnemy : public EnemyBase {
 public:
  PinkSlimeEnemy() : EnemyBase() {
    auto animator = Component::Create<Animator>("resources/sprites/enemies/slime_pink.png",
                                                4, Point{16, 16}, Point{2, 2});
    animator->SetSpriteSheetAtIndex("resources/sprites/enemies/slime_pink.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->Play(true);

    AddComponent(animator);

    auto logic = GetComponentByType<EnemyLogic>();
    logic->SetExperienceAmount(2);

    auto collider = Component::Create<BoxCollider>(Vector2d{60, 60});
    auto rigid_body = Component::Create<RigidBody>(*this, engine::physics::RigidBodyType::Dynamic, collider);
    AddComponent(rigid_body);
    AddComponent(collider);

    GetTransform()->SetSize({60, 60});
  }

  static std::shared_ptr<EnemyBase> Create() {
    auto object = GameObject::Create<PinkSlimeEnemy>();

    auto rigid_body = object->GetComponentByType<RigidBody>();
    rigid_body->Register();

    object->SetIsActive(false);
    return object;
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_PINK_SLIME_ENEMY_H_
