#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/structs/input.h"
#include "entities/structs/vector_2d.h"
#include "utility/timer.h"
#include "player/projectile/projectile_object_pool.h"
#include <math.h>

using namespace engine::entities;

namespace slime_shooter {

class PlayerWeaponLogic : public BehaviourScript {
 public:
  void SetCanShoot(bool can_shoot) {
    can_shoot_ = can_shoot;
    weapon_sprite_->SetColor(can_shoot_ ? Color{255, 255, 255} : Color{255, 0, 0});
  }

 private:
  bool can_shoot_ = true;
  Point position_offset_ = {12, 65};
  const float max_fire_rate_ = 0.075f;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Transform> parent_transform_;
  std::shared_ptr<Sprite> weapon_sprite_;
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<AudioSource> shooting_sound_;
  engine::utility::Timer timer_{};

  void OnStart() override {
    transform_ = GetGameObject().GetTransform();
    parent_transform_ = GetGameObject().GetParent()->GetTransform();
    weapon_sprite_ = GetGameObject().GetComponentByType<Sprite>();
    player_statistics_ = GetGameObject().GetParent()->GetComponentByType<Statistics>();
    transform_->Position = GetGameObject().GetParent()->GetTransform()->Position;

    shooting_sound_ = Component::Create<AudioSource>("resources/audio/player_shoot.wav");
    shooting_sound_->SetVolume(10);
    shooting_sound_->SetSpeed(75);
    GetGameObject().AddComponent(shooting_sound_);

    timer_.Start();
  }

  void OnInput() override {
    UpdatePosition();
    ProcessBulletFiring();
  }

  void UpdatePosition() {
    transform_->Position = {
        parent_transform_->Position.x + position_offset_.x,
        parent_transform_->Position.y + position_offset_.y
    };
  }

  void ProcessBulletFiring() {
    if (!timer_.HasElapsed(GetFireRate()) || !can_shoot_) return;

    Vector2d direction {0, 0};

    for (auto key : Input::GetActiveKeys()) {
      if (key == Key::UnoUpArrow) direction.y--;
      if (key == Key::UnoDownArrow) direction.y++;
      if (key == Key::UnoLeftArrow) direction.x--;
      if (key == Key::UnoRightArrow) direction.x++;
    }

    if (direction.x == 0 && direction.y == 0) return;

    timer_.Start();

    direction.Normalize();

    float player_position_center_offset = 85.0f;

    Vector2d target_position = {
        (parent_transform_->Position.x + parent_transform_->GetSize().x/2) + direction.x * player_position_center_offset,
        (parent_transform_->Position.y + parent_transform_->GetSize().y/2) + direction.y * player_position_center_offset
    };

    auto bullet = ProjectileObjectPool::GetInstance().Acquire();
    bullet->GetTransform()->Position = target_position;
    bullet->GetComponentByType<RigidBody>()->SetPosition(target_position);

    float rotation_degrees = atan2(direction.y, direction.x) * (180.0f / M_PI);

    rotation_degrees += 90;

    if (rotation_degrees < 0.0f)
      rotation_degrees += 360.0f;

    bullet->GetTransform()->SetRotation(rotation_degrees);
    transform_->SetRotation(rotation_degrees);

    bullet->GetComponentByType<ProjectileLogic>()->SetDirection(direction);

    shooting_sound_->Play();
  }

  double GetFireRate() {
    float fire_rate = player_statistics_->Get(StatisticType::FireRate);
    return fire_rate >= max_fire_rate_ ? fire_rate : max_fire_rate_;
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_LOGIC_H_
