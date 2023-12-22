#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_KEY_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_KEY_H_

namespace engine::entities {

/// @brief Generic Key struct used in i.e. key listener functions
enum class Key {
  // Arrow keys
  UnoUpArrow,
  UnoDownArrow,
  UnoLeftArrow,
  UnoRightArrow,

  // Mouse buttons
  UnoLeftMouseButton,
  UnoRightMouseButton,

  // Alphabet letters
  UnoA,
  UnoB,
  UnoC,
  UnoD,
  UnoE,
  UnoF,
  UnoG,
  UnoH,
  UnoI,
  UnoJ,
  UnoK,
  UnoL,
  UnoM,
  UnoN,
  UnoO,
  UnoP,
  UnoQ,
  UnoR,
  UnoS,
  UnoT,
  UnoU,
  UnoV,
  UnoW,
  UnoX,
  UnoY,
  UnoZ,
  // Digits
  Uno0,
  Uno1,
  Uno2,
  Uno3,
  Uno4,
  Uno5,
  Uno6,
  Uno7,
  Uno8,
  Uno9,

  // Special characters
  UnoBackspace,
  UnoTab,
  UnoSpace,
  UnoLeftControl,
  UnoLeftShift,
  UnoRightControl,
  UnoRightShift,
  UnoPageUp,
  UnoPageDown,
  UnoHome,

  // F-keys
  UnoF1,
  UnoF2,
  UnoF3,
  UnoF4,
  UnoF5,
  UnoF6,
  UnoF7,
  UnoF8,
  UnoF9,
  UnoF10,
  UnoF11,
  UnoF12,

  // Events
  UnoWindowClosed,

  // Default/reset value
  UnoNone,
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_KEY_H_
