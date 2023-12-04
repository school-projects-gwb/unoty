#ifndef SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_OBJECT_POOL_H_
#define SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_OBJECT_POOL_H_

#include "experience.h"
#include "utility/object_pool.h"
#include "utility/randomizer.h"
using namespace engine::entities;

class Experience;
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
  ObjectPool<Experience> experience_object_pool_;

  ExperienceObjectPool() : experience_object_pool_(AcquireCallback, ReleaseCallback) {
    experience_object_pool_.PoolObjects(100, Experience::Create, true);
  }

  static std::shared_ptr<Experience> AcquireCallback(std::vector<std::shared_ptr<Experience>> objects) {
    auto object = Randomizer::GetInstance().RandomElement(objects);
    if (object.has_value()) {
      object.value()->SetIsActive(true);
      return object.value();
    }

    return nullptr;
  }

  static void ReleaseCallback(std::shared_ptr<Experience> obj) { obj->SetIsActive(false); }
};

}

#endif //SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_OBJECT_POOL_H_
