#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_SPRITE_ANIMATION_STATE_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_SPRITE_ANIMATION_STATE_H_

namespace engine::entities {

/// @brief Enum used for Sprite Animation states for "human readable" state symbols
enum SpriteAnimationState {
  Default, North, South, West, East,
  NorthEast, NorthWest, SouthEast, SouthWest,
  Reset
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_SPRITE_ANIMATION_STATE_H_
