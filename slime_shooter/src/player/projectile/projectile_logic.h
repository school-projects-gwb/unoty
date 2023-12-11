#ifndef SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_LOGIC_H_
#define SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_LOGIC_H_

#include "entities/behaviour_script.h"
#include "engine/engine.h"
#include "enemies/enemy_object_pool.h"

using namespace engine::entities;

namespace slime_shooter {

class ProjectileLogic : public BehaviourScript {
 public:
  void SetDirection(Vector2d direction_vector) {
    direction_vector_ = direction_vector;
  }

 private:
  Vector2d direction_vector_;
  const float projectile_speed_ = 5;

  void OnUpdate() override {
    auto vector = direction_vector_;
    vector.Normalize();

    vector.x *= projectile_speed_;
    vector.y *= projectile_speed_;

    engine::Engine::GetInstance().GetPhysicsEngine()->SetLinearVelocity(GetGameObject(), vector);
  }

  void OnCollisionEnter(engine::entities::GameObject *&colliding_object) override {
    auto tag_name = colliding_object->GetTagName();

    if (tag_name != "enemy" && colliding_object->GetName() != "Player") {
      GetGameObject().SetIsActive(false);
      return;
    }

    if (tag_name != "enemy") return;

    auto enemy = GameObject::Cast<EnemyBase>(colliding_object);
    enemy->TakeDamage(false);

    GetGameObject().SetIsActive(false);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_LOGIC_H_
