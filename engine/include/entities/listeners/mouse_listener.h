#ifndef ENGINE_INCLUDE_ENTITIES_LISTENERS_MOUSE_LISTENER_H_
#define ENGINE_INCLUDE_ENTITIES_LISTENERS_MOUSE_LISTENER_H_

#include <memory>
#include "listener.h"

namespace engine::entities {

/// @brief Triggers functions on mouse interaction
class MouseListener : public Listener {
 public:
  ~MouseListener();
  MouseListener();
  virtual void OnMouseMoved();
  virtual void OnMouseClicked();
  virtual void OnMousePressed();
  virtual void OnMouseReleased();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_LISTENERS_MOUSE_LISTENER_H_
