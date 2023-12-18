#ifndef ENGINE_INCLUDE_ENTITIES_BEHAVIOUR_SCRIPT_H_
#define ENGINE_INCLUDE_ENTITIES_BEHAVIOUR_SCRIPT_H_

#include <memory>
#include "entities/physics/collider.h"
#include "entities/structs/key.h"
namespace engine::entities {

/// @brief Use for completely custom behavior; has access to various listeners
class BehaviourScript : public Component {
 public:
  ~BehaviourScript();
  BehaviourScript();
  virtual void OnStart();
  virtual void OnUpdate();
  virtual void OnInput();
  virtual void OnCollisionEnter(GameObject* &colliding_object);
  virtual void OnCollisionExit(GameObject* &colliding_object);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_BEHAVIOUR_SCRIPT_H_
