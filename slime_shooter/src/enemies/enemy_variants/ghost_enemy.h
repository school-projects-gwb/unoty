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
    auto animator = Component::Create<Animator>("resources/sprites/enemies/ghost.png", 4, Point{16, 16}, Point{2, 2});
    AddComponent(animator);

    auto attack = Component::Create<EnemyAttack>(*this);
    AddComponent(attack);

    auto logic = GetComponentByType<EnemyLogic>();
    logic->SetExperienceAmount(2);

    auto collider = Component::Create<BoxCollider>(Vector2d{75, 75});
    auto rigid_body = Component::Create<RigidBody>(*this, engine::physics::RigidBodyType::Dynamic, collider);
    AddComponent(rigid_body);
    AddComponent(collider);

    GetTransform()->SetSize({75, 75});
  }

  static std::shared_ptr<EnemyBase> Create() {
    auto object = GameObject::Create<GhostEnemy>();

    auto rigid_body = object->GetComponentByType<RigidBody>();
    rigid_body->Register();

    object->SetIsActive(false);
    return object;
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_VARIANTS_GHOST_ENEMY_H_
