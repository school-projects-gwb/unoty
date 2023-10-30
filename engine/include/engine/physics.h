#ifndef ENGINE_SRC_PHYSICS_PHYSICS_H_
#define ENGINE_SRC_PHYSICS_PHYSICS_H_

namespace engine::physics {

class Physics {
 public:
  virtual ~Physics() = default;
  virtual void Initialize() = 0;
  virtual void AddBody(/* todo params */) = 0;
  virtual void Step(float time_step) = 0;
};

}

#endif //ENGINE_SRC_PHYSICS_PHYSICS_H_
