#ifndef ENGINE_INCLUDE_ENTITIES_LISTENERS_KEY_LISTENER_H_
#define ENGINE_INCLUDE_ENTITIES_LISTENERS_KEY_LISTENER_H_

#include <memory>
#include "entities/structs/key.h"
#include "listener.h"

namespace engine::entities {

/// @brief Triggers functions on key interaction
class KeyListener : public Listener {
 public:
  ~KeyListener() override;
  KeyListener();
  virtual void OnKeyPressed();
  virtual void OnKeyReleased();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_LISTENERS_KEY_LISTENER_H_
