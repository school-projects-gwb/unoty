#ifndef SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_ATTACK_H_
#define SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_ATTACK_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/structs/vector_2d.h"
#include "utility/debug.h"
#include "projectiles/enemy_projectile_object_pool.h"
#include "config/projectile_config.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemyAttack : public BehaviourScript {
 public:
  explicit EnemyAttack(GameObject &game_object) {
    transform_ = game_object.GetTransform();
    shooting_sound_ = Component::Create<AudioSource>("resources/audio/player_shoot.wav");
    shooting_sound_->SetVolume(10);
    game_object.AddComponent(shooting_sound_);
    attack_delay_timer_.Start();
  }

  void StartAttack() {
    if (!is_target_set_) {
      engine::utility::Debug::Log("Enemy tried attacking without having a target set, setting target to default (player)");
      SetPlayerAsTarget();
    }
    can_shoot_ = true;
  }

  void SetTarget(std::shared_ptr<Transform> target) {
    target_transform_ = std::move(target);
    is_target_set_ = true;
  }

  void SetPlayerAsTarget() {
    auto player = GameObject::GetSceneObjectByName("Player");
    if (player)
      SetTarget(player->GetTransform());
  }

  void ClearTarget() {
    target_transform_.reset();
    is_target_set_ = false;
  }

  void SetFireRate(float amount) {
    fire_rate_ = amount < min_fire_rate_ ? min_fire_rate_ : amount;
  }

  [[nodiscard]] float GetFireRate() const {
    return fire_rate_;
  }

 private:
  bool can_shoot_ = false;
  bool is_target_set_ = false;
  float fire_rate_ = ProjectileConfig::default_enemy_fire_rate;
  const float min_fire_rate_ = ProjectileConfig::min_fire_rate;
  float max_attack_distance_ = ProjectileConfig::max_attack_distance;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Transform> target_transform_;
  std::shared_ptr<AudioSource> shooting_sound_;
  engine::utility::Timer attack_delay_timer_{};

  void OnInput() override {
    if (!attack_delay_timer_.HasElapsed(fire_rate_) || !can_shoot_ || !is_target_set_ || !IsInAttackDistance())
      return;

    attack_delay_timer_.Start();

    Vector2d direction = target_transform_->Position - transform_->Position;
    direction.Normalize();

    float offset = 85.0f;

    Vector2d offset_spawn_position = {
        (transform_->Position.x + transform_->GetSize().x / 2) + direction.x * offset,
        (transform_->Position.y + transform_->GetSize().y / 2) + direction.y * offset
    };

    auto bullet = EnemyProjectileObjectPool::GetInstance().Acquire();
    bullet->GetTransform()->Position = offset_spawn_position;
    bullet->GetComponentByType<RigidBody>()->SetPosition(offset_spawn_position);

    float rotation_degrees = atan2(direction.y, direction.x) * (180.0f / M_PI) + 90;

    if (rotation_degrees < 0.0f)
      rotation_degrees += 360.0f;

    bullet->GetTransform()->SetRotation(rotation_degrees);
    auto projectile_logic = bullet->GetComponentByType<ProjectileLogic>();
    projectile_logic->SetDirection(direction);
    projectile_logic->SetSourceTag("Enemy");

    shooting_sound_->Play();
  }

  bool IsInAttackDistance() {
    if (!transform_ || !target_transform_ || max_attack_distance_ <= 0.0f)
      return true;

    return transform_->Position.Distance(target_transform_->Position) <= max_attack_distance_;
  }

};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_ATTACK_H_
