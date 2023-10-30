#ifndef ENGINE_INCLUDE_ENTITIES_BEHAVIOUR_SCRIPT_H_
#define ENGINE_INCLUDE_ENTITIES_BEHAVIOUR_SCRIPT_H_

#include <memory>
#include "entities/colliders/collider.h"
#include "entities/structs/key.h"
namespace engine::entities {

/// @brief Use for completely custom behavior; has access to various listeners
class BehaviourScript : public Component {
 public:
  ~BehaviourScript();
  BehaviourScript();
  virtual void OnStart() = 0;
  virtual void OnUpdate() = 0;
  virtual void OnInput(const Key& key) = 0;
  virtual void OnTriggerEnter2d(Collider& collider) = 0;
  virtual void OnTriggerExit2d(Collider& collider) = 0;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_BEHAVIOUR_SCRIPT_H_
