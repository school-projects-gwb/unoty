#ifndef ENGINE_INCLUDE_ENTITIES_LISTENERS_MOUSE_LISTENER_H_
#define ENGINE_INCLUDE_ENTITIES_LISTENERS_MOUSE_LISTENER_H_

namespace engine::entities {

/// @brief Triggers functions on mouse interaction
class MouseListener {
 public:
  virtual ~MouseListener() = default;

  virtual void OnMouseMoved() = 0;
  virtual void OnMouseClicked() = 0;
  virtual void OnMousePressed() = 0;
  virtual void OnMouseReleased() = 0;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_LISTENERS_MOUSE_LISTENER_H_
