#ifndef SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_SPAWNER_LOGIC_H_
#define SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_SPAWNER_LOGIC_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/structs/input.h"
#include "entities/structs/vector_2d.h"
#include "statistics/statistics.h"
#include "utility/timer.h"
#include "utility/object_pool.h"
#include "enemy_object_pool.h"
#include "random"

using namespace engine::entities;

namespace slime_shooter {

class EnemySpawnerLogic : public BehaviourScript {
 public:
  EnemySpawnerLogic() : timer_() {}

  void OnStart() override {
    timer_.Start();

    auto player = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player->GetComponentByType<Statistics>();
  }

  void OnUpdate() override {
    ProcessSpawnRateChange();
    if (timer_.GetElapsedSeconds() < spawn_rate_seconds_ || !can_spawn_) return;
    SpawnEnemy();
    timer_.Start();
  }

 private:
  bool can_spawn_ = true;
  std::shared_ptr<Statistics> player_statistics_;
  float spawn_rate_seconds_ = 3.5; // TODO reset at some point (default is 1.4f)
  int spawn_rate_changed_counter_ = 0;
  engine::utility::Timer timer_;
  int min_x = 100, min_y = 100, max_x = 1700, max_y = 1275;

  void ProcessSpawnRateChange() {
    int player_level = player_statistics_->GetInt(StatisticType::Level);

    if (spawn_rate_changed_counter_ == 0 && player_level >= 3) {
      spawn_rate_seconds_ = 1.2f;
      spawn_rate_changed_counter_++;
    }

    if (spawn_rate_changed_counter_ == 1 && player_level >= 8) {
      spawn_rate_seconds_ = 0.9f;
      spawn_rate_changed_counter_++;
    }
  }

  void SpawnEnemy() {
    auto enemy = EnemyObjectPool::GetInstance().Acquire();
    if (enemy == nullptr) return;

    int enemy_pos_x =
        engine::utility::Randomizer::GetInstance().RandomInt(min_x, max_x); // Get x-position within bounds
    int enemy_pos_y =
        engine::utility::Randomizer::GetInstance().RandomBool() ? min_y : max_y; // Randomly spawn at top or bottom

    if (enemy->GetComponentByType<EnemyAttack>()) enemy->GetComponentByType<EnemyAttack>()->StartAttack();

    enemy->GetTransform()->Position = {enemy_pos_x, enemy_pos_y};
    enemy->GetComponentByType<RigidBody>()->SetPosition({enemy_pos_x, enemy_pos_y});
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_SPAWNER_LOGIC_H_
