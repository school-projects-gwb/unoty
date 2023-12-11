#ifndef SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_H_
#define SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_H_

#include "entities/game_object.h"
#include "entities/sprite.h"
#include "projectile_logic.h"
#include "entities/colliders/circle_collider.h"
#include "entities/rigid_body.h"
using namespace engine::entities;

namespace slime_shooter {

class Projectile : public GameObject {
 public:
  Projectile() {
    auto sprite = Component::Create<Sprite>("resources/sprites/player/bullet.png");
    auto projectile_logic = Component::Create<ProjectileLogic>();

    auto collider = Component::Create<BoxCollider>(Vector2d{30, 30});
    auto rigid_body = Component::Create<RigidBody>(*this, engine::physics::RigidBodyType::Dynamic, collider);

    AddComponent(sprite);
    AddComponent(projectile_logic);
    AddComponent(rigid_body);
    AddComponent(collider);

    GetTransform()->SetSize({30, 30});
    SetLayer(3);
    SetTagName("projectile");
  }

  static std::shared_ptr<Projectile> Create() {
    auto object = GameObject::Create<Projectile>();
    auto rigid_body = object->GetComponentByType<RigidBody>();
    rigid_body->Register();

    object->SetIsActive(false);

    return object;
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_H_
