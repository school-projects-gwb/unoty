#ifndef ENGINE_SRC_PHYSICS_IMPL_PHYSICS_H_
#define ENGINE_SRC_PHYSICS_IMPL_PHYSICS_H_

#include "engine/physics.h"
namespace engine::physics {

class ImplPhysics : public Physics {
 public:
  ImplPhysics();
  void Initialize() override;
  void AddBody() override;
  void Step(float time_step) override;
};

}

#endif //ENGINE_SRC_PHYSICS_IMPL_PHYSICS_H_
