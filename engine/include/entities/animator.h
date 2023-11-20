#ifndef ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_
#define ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_

#include "component.h"
#include "entities/structs/sprite_animation_state.h"
#include "rendering/renderer.h"

namespace engine::entities {

class Animator : public Component {
 public:
  ~Animator();

  /// @brief Initialises Animator by setting default sprite path and sprite sheet information
  ///
  /// \param default_state_sprite_path The initial sprite value and also the static sprite that's rendered when the animation isn't active.
  /// \param sprites_in_sheet The total amount of sprites in the sheet
  /// \param sprite_pixel_size The per-sprite (individual) sprite pixel size that EACH sprite in the sprite sheet is equal to.
  /// \param sheet_row_col_count The amount of rows and columns in the sheet
  Animator(std::string default_state_sprite_path, int sprites_in_sheet = 4, Point sprite_pixel_size = {32, 32}, Point sheet_row_col_count = {2, 2});

  /// @brief Plays animation of current SpriteSheet
  void Play(bool is_looping);
  
  /// @brief Updates current animation state ticker when animation is playing and renders sprite
  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<entities::Transform> transform);

  /// @brief Stops animation; resets to Default Sprite
  void Stop();

  /// @brief Adds spritesheet at path with given index key so that it can set later on
  void SetSpriteSheetAtIndex(const std::string& sprite_path, entities::SpriteAnimationState index);

  /// @overload with integer value when SpriteAnimationState isn't applicable
  void SetSpriteSheetAtIndex(const std::string& sprite_path, int index);

  /// @overload Sets the sprite animation at the given state (Same state used when Adding)
  void SetCurrentAnimationSpriteSheet(entities::SpriteAnimationState state);

  /// @overload with integer value when SpriteAnimationState isn't applicable
  void SetCurrentAnimationSpriteSheet(int index);

  /// @brief Used when no animation is currently active, behaves like regular Sprite Component
  void SetDefaultStateSprite(const std::string& sprite_path);

  /// @brief Sets flip for both sprites in sheet and default animation state Sprite
  void SetFlip(entities::SpriteFlip flip);

  /// @brief Sets color overlay for both sprites in sheet and default animation state Sprite
  void SetColor(entities::Color color);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_
