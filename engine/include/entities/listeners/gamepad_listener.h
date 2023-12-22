#ifndef ENGINE_INCLUDE_ENTITIES_LISTENERS_GAMEPAD_LISTENER_H
#define ENGINE_INCLUDE_ENTITIES_LISTENERS_GAMEPAD_LISTENER_H

#include <memory>

#include "listener.h"

namespace engine::entities {

/// @brief Triggers functions on gamepad interaction.
class GamepadListener : public Listener {
 public:
  ~GamepadListener() override;
  GamepadListener();
  virtual void OnButtonPressed();
  virtual void OnButtonReleased();
  virtual void OnLeftStickMoved();
  virtual void OnRightStickMoved();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

} // namespace engine::entities

#endif //ENGINE_INCLUDE_ENTITIES_LISTENERS_GAMEPAD_LISTENER_H
