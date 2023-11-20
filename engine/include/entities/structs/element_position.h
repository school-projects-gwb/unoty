#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_ELEMENT_POSITION_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_ELEMENT_POSITION_H_

namespace engine::entities {

/// @brief Used for i.e. positioning text at a specific location in to the window
enum ElementPosition {
  TopLeft, TopRight, BottomLeft, BottomRight, CustomPosition
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_ELEMENT_POSITION_H_
