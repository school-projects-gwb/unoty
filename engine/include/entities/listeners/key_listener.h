#ifndef ENGINE_INCLUDE_ENTITIES_LISTENERS_KEY_LISTENER_H_
#define ENGINE_INCLUDE_ENTITIES_LISTENERS_KEY_LISTENER_H_

namespace game::entities {

/// @brief Triggers functions on key interaction
class KeyListener {
 public:
  virtual ~KeyListener() = default;

  virtual void OnKeyPressed() = 0;
  virtual void OnKeyReleased() = 0;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_LISTENERS_KEY_LISTENER_H_
