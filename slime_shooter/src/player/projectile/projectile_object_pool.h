#ifndef SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_OBJECT_POOL_H_
#define SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_OBJECT_POOL_H_

#include "projectile.h"
#include "utility/object_pool.h"
#include "utility/randomizer.h"

using namespace engine::entities;

namespace slime_shooter {

class ProjectileObjectPool {
 public:
  static ProjectileObjectPool& GetInstance() {
    static ProjectileObjectPool instance;
    return instance;
  }

  std::shared_ptr<Projectile> Acquire() {
    return projectile_object_pool_.Acquire();
  }

  void Release(std::shared_ptr<Projectile> enemy_object) {
    projectile_object_pool_.Release(enemy_object);
  }

 private:
  engine::utility::ObjectPool<Projectile> projectile_object_pool_;

  ProjectileObjectPool() : projectile_object_pool_(AcquireCallback, ReleaseCallback, [this](){PoolObjects();}) {
    projectile_object_pool_.PoolObjects(100, Projectile::Create);
  }

  void PoolObjects() {
    projectile_object_pool_.PoolObjects(100, Projectile::Create);
  }

  static std::shared_ptr<Projectile> AcquireCallback(std::vector<std::weak_ptr<Projectile>> objects) {
    auto weak_object = engine::utility::Randomizer::GetInstance().RandomElement(objects);
    auto object = weak_object.value().lock();

    if (object) {
      object->SetIsActive(true);
      return object;
    }

    return nullptr;
  }

  static void ReleaseCallback(std::shared_ptr<Projectile> obj) { obj->SetIsActive(false); }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_SLIME_SHOOTER_SRC_PLAYER_PROJECTILE_PROJECTILE_OBJECT_POOL_H_
