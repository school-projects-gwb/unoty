#ifndef SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_LOGIC_H_
#define SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_LOGIC_H_

#include "entities/behaviour_script.h"
#include "engine/engine.h"
#include "enemies/enemy_variants/enemy_base.h"
#include "config/projectile_config.h"

using namespace engine::entities;

namespace slime_shooter {

class ProjectileLogic : public BehaviourScript {
 public:
  void SetDirection(Vector2d direction_vector) {
    direction_vector_ = direction_vector;
  }

  void SetSourceTag(const std::string &source) {
    source_tag_ = source;
  }

 private:
  Vector2d direction_vector_;
  const float projectile_speed_ = ProjectileConfig::projectile_speed;
  std::string source_tag_;

  void OnUpdate() override {
    auto vector = direction_vector_;
    vector.Normalize();

    vector.x *= projectile_speed_;
    vector.y *= projectile_speed_;

    engine::Engine::GetInstance().GetPhysicsEngine()->SetLinearVelocity(GetGameObject(), vector);
  }

  void OnCollisionEnter(engine::entities::GameObject *&colliding_object) override {
    auto colliding_object_tag = colliding_object->GetTagName();

    if (colliding_object_tag.empty() || colliding_object_tag == "PlayerWeapon")
      return;

    // Valid collision between player-shot projectile and enemy
    if (source_tag_ == "Player" && colliding_object_tag == "Enemy") {
      auto enemy = GameObject::Cast<EnemyBase>(colliding_object);
      enemy->TakeDamage(false);
      GetGameObject().SetIsActive(false);
      return;
    }

    // Valid collision between enemy-shot projectile and player
    if (source_tag_ == "Enemy" && colliding_object_tag == "Player") {
      auto player_health = colliding_object->GetComponentByType<PlayerHealth>();
      if (player_health)
        player_health->TakeDamage(1);

      GetGameObject().SetIsActive(false);
      return;
    }

    // Colliding bullets can either ignore or destroy eachother, depends on config
    if (ProjectileConfig::projectile_collision && colliding_object_tag == "Projectile")
      GetGameObject().SetIsActive(false);

    if (colliding_object_tag == "Wall")
      GetGameObject().SetIsActive(false);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_LOGIC_H_
