#ifndef SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_H_
#define SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_H_

#include "entities/game_object.h"
#include "entities/sprite.h"
#include "projectile_logic.h"
#include "entities/physics/box_collider.h"
#include "entities/physics/rigid_body.h"

using namespace engine::entities;

namespace slime_shooter {

class Projectile : public GameObject {
 public:
  explicit Projectile(const std::string &sprite_path) {
    auto sprite = Component::Create<Sprite>(sprite_path);
    auto projectile_logic = Component::Create<ProjectileLogic>();
    projectile_logic->SetSourceTag("None");

    auto collider = Component::Create<BoxCollider>(Vector2d{30, 30});
    collider->SetIsSensor(true);
    auto rigid_body = Component::Create<RigidBody>(*this, engine::physics::RigidBodyType::Dynamic, collider);

    AddComponent(sprite);
    AddComponent(projectile_logic);
    AddComponent(rigid_body);
    AddComponent(collider);

    GetTransform()->SetSize({30, 30});
    SetLayer(3);
    SetTagName("Projectile");
  }

  static std::shared_ptr<Projectile> CreatePlayerProjectile() {
    return CreateProjectile("resources/sprites/player/bullet.png");
  }

  static std::shared_ptr<Projectile> CreateEnemyProjectile() {
    return CreateProjectile("resources/sprites/enemies/enemy_bullet.png");
  }

 private:
  static std::shared_ptr<Projectile> CreateProjectile(const std::string &sprite_path) {
    auto projectile = GameObject::Create<Projectile>(sprite_path);
    auto rigid_body = projectile->GetComponentByType<RigidBody>();
    rigid_body->Register();
    //Initialize at a random position, avoids the projectile_pool spawning 100 projectiles that instantly collide
    rigid_body->SetPosition({engine::utility::Randomizer::GetInstance().RandomInt(0, 1000), engine::utility::Randomizer::GetInstance().RandomInt(0, 1000)});


    projectile->SetIsActive(false);

    return projectile;
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_H_
