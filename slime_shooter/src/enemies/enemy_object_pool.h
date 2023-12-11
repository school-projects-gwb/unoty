#ifndef SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_OBJECT_POOL_H_
#define SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_OBJECT_POOL_H_

#include "enemies/enemy_variants/enemy_base.h"
#include "enemies/enemy_variants/pink_slime_enemy.h"
#include "utility/object_pool.h"
#include "enemies/enemy_variants/ghost_enemy.h"
#include "enemies/enemy_variants/orange_slime_enemy.h"
#include "utility/randomizer.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemyObjectPool {
 public:
  static EnemyObjectPool& GetInstance() {
    static EnemyObjectPool instance;
    return instance;
  }

  std::shared_ptr<EnemyBase> Acquire() {
    return enemy_object_pool_.Acquire();
  }

  void Release(std::shared_ptr<EnemyBase> enemy_object) {
    enemy_object_pool_.Release(enemy_object);
  }

 private:
  engine::utility::ObjectPool<EnemyBase> enemy_object_pool_;

  EnemyObjectPool() : enemy_object_pool_(AcquireCallback, ReleaseCallback, [this](){PoolObjects();}) {
  }

  void PoolObjects() {
    enemy_object_pool_.PoolObjects(50, GhostEnemy::Create);
    enemy_object_pool_.PoolObjects(50, PinkSlimeEnemy::Create);
    enemy_object_pool_.PoolObjects(50, OrangeSlimeEnemy::Create);
  }

  static std::shared_ptr<EnemyBase> AcquireCallback(std::vector<std::weak_ptr<EnemyBase>> objects) {
    std::vector<std::shared_ptr<EnemyBase>> available_objects;

    for (const auto &weak_object : objects) {
      auto object = weak_object.lock();
      if (!object) continue;

      if (object->GetIsActive()) continue;
      available_objects.push_back(object);
    }

    if (available_objects.empty()) return nullptr;

    auto target_object = engine::utility::Randomizer::GetInstance().RandomElement(available_objects);
    if (!target_object.has_value()) return nullptr;

    target_object.value()->SetIsActive(true);
    return target_object.value();
  }

  static void ReleaseCallback(std::shared_ptr<EnemyBase> obj) { obj->SetIsActive(false); }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_OBJECT_POOL_H_
