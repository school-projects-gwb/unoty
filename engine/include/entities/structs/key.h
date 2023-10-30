#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_KEY_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_KEY_H_

namespace engine::entities {

/// @brief Generic Key struct used in i.e. key listener functions
enum class Key {
  Up,
  Down,
  Left,
  Right,
  LeftMouse,
  RightMouse,
  None,
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_KEY_H_
