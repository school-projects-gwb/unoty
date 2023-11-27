#ifndef SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_LOGIC_H_
#define SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_LOGIC_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/structs/input.h"
#include "statistics/statistics.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemyLogic : public BehaviourScript {
 public:
  void OnStart() override {
    Initialise();
  }

  void OnUpdate() override {
    if (!is_initialised_) Initialise(); // Not initialised when object is added through object pool "at runtime"

    auto target_position = target_transform_->Position;
    auto current_position = transform_->Position;

    int delta_x = target_position.x - current_position.x;
    int delta_y = target_position.y - current_position.y;

    Vector2d vector = {delta_x, delta_y};
    vector.normalize();

    current_position.x += vector.x * speed_;
    current_position.y += vector.y * speed_;

    transform_->Position = {current_position.x, current_position.y};
  }

 private:
  bool is_initialised_ = false;
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Transform> target_transform_;

  float original_speed_ = 2;
  float original_health_ = 1;
  const int experience_ = 2;

  float speed_ = 2;
  float health_ = 1;

  void Initialise() {
    auto player = GameObject::GetSceneObjectByName("Player");

    player_statistics_ = player->GetComponentByType<Statistics>();
    target_transform_ = player->GetTransform();
    transform_ = GetGameObject().GetTransform();

    ResetStatistics();

    is_initialised_ = true;
  }

  void ResetStatistics() {
    original_speed_ = speed_;
    original_health_ = health_;

    auto player_level = player_statistics_->GetInt(StatisticType::Level);
    auto damage_modifier = player_level * 0.5;

    if (player_level >= 15 && player_level < 25) {
      damage_modifier = player_level * 2;
    } else if (player_level >= 35 && player_level < 50) {
      damage_modifier = player_level * 2;
    } else if (player_level >= 50 && player_level < 75) {
      damage_modifier = player_level * 3.5;
    } else if (player_level >= 75 && player_level < 100) {
      damage_modifier = player_level * 4.35;
    } else if (player_level > 100) {
      damage_modifier = player_level * 6.5;
    }

    health_ = (float)(original_health_ + damage_modifier);
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_LOGIC_H_
