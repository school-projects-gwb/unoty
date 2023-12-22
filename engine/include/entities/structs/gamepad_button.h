#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_GAMEPAD_BUTTON_H
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_GAMEPAD_BUTTON_H

namespace engine::entities {

enum class GamepadButton {
  // Letter buttons
  Y,
  B,
  A,
  X,

  // DPad
  Up,
  Right,
  Down,
  Left,

  // Middle buttons
  Start,
  Back,
  Guide,

  // Shoulder buttons
  LeftShoulder,
  RightShoulder,

  // Joysticks
  LeftJoystick,
  RightJoystick,

  // None
  None,

};

} // namespace engine::entities

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_GAMEPAD_BUTTON_H
