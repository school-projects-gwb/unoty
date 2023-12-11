#ifndef SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_OBJECT_POOL_H_
#define SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_OBJECT_POOL_H_

#include "experience.h"
#include "utility/object_pool.h"
#include "utility/randomizer.h"
using namespace engine::entities;

namespace slime_shooter {

class ExperienceObjectPool {
 public:
  static ExperienceObjectPool& GetInstance() {
    static ExperienceObjectPool instance;
    return instance;
  }

  std::shared_ptr<Experience> Acquire() {
    return experience_object_pool_.Acquire();
  }

  void Release(std::shared_ptr<Experience> enemy_object) {
    experience_object_pool_.Release(enemy_object);
  }

 private:
  engine::utility::ObjectPool<Experience> experience_object_pool_;

  ExperienceObjectPool() : experience_object_pool_(AcquireCallback, ReleaseCallback, [this](){PoolObjects();}) {
  }

  void PoolObjects() {
    experience_object_pool_.PoolObjects(100, Experience::Create);
  }

  static std::shared_ptr<Experience> AcquireCallback(std::vector<std::weak_ptr<Experience>> objects) {
    auto weak_object = engine::utility::Randomizer::GetInstance().RandomElement(objects);
    auto object = weak_object.value().lock();

    if (object) {
      object->SetIsActive(true);
      return object;
    }

    return nullptr;
  }

  static void ReleaseCallback(std::shared_ptr<Experience> obj) { obj->SetIsActive(false); }
};

}

#endif //SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_OBJECT_POOL_H_
