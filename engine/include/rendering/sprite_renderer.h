#ifndef ENGINE_INCLUDE_SPRITE_RENDERER_H_
#define ENGINE_INCLUDE_SPRITE_RENDERER_H_

#include "entities/camera.h"
#include "entities/structs/rectangle.h"
#include "entities/structs/sprite_flip.h"
#include "string"
#include "entities/structs/element_position.h"
#include "entities/structs/point.h"

namespace engine::ui {

struct RenderInfo {
  std::string sprite_path;
  std::shared_ptr<entities::Transform> transform;
  entities::structs::Rectangle position_in_sheet;
  entities::structs::Rectangle target_position;
  entities::Point size = {0,0};
  bool is_ui_object = false;
};

struct RenderOptions {
  entities::SpriteFlip flip = entities::FlipNone;
  entities::Color color = {255, 255, 255};
  bool is_position_fixed = false;
};

class SpriteRenderer {
 public:
  virtual ~SpriteRenderer() = default;

  virtual void Init(void* renderer, int window_width, int window_height) = 0;

  virtual void RenderRectangle(const RenderInfo& render_info, const RenderOptions& render_options) = 0;

  /// @brief Renders basic sprite based on path and positional information in Transform
  virtual void RenderSprite(const RenderInfo& render_info, const RenderOptions& render_options) = 0;

  /// @overload Renders basic sprite with color modulation
  virtual void RenderSpriteWithColorOverlay(const RenderInfo& render_info, const RenderOptions& render_options) = 0;

  /// @brief Renders simple sprite from sheet without additional logic for rotation, flip, scaling etc.
  ///
  /// Used for i.e. static tile map rendering
  /// @overload
  virtual void RenderStaticSpriteFromSheet(const RenderInfo& render_info, const RenderOptions& render_options) = 0;

  /// @brief Renders sprite from sheet with all the same options as RenderSprite
  virtual void RenderSpriteFromSheet(const RenderInfo& render_info, const RenderOptions& render_options) = 0;

  /// @overload Renders sprite from sheet with all the same options as RenderSprite including a Color Overlay
  virtual void RenderSpriteFromSheetWithColorOverlay(const RenderInfo& render_info, const RenderOptions& render_optionsp) = 0;

  virtual void RenderDebugRectangles(const std::vector<std::pair<entities::Vector2d, entities::Vector2d>> &debug_rectangles) = 0;

  /// @overload After calling, all rendered objects will be considered as lights on top of the background/game layer
  virtual void StartLightLayer(const entities::Color &lighting_color) = 0;

  virtual void StartRenderFrame() = 0;
  virtual void EndRenderFrame() = 0;

  /// @overload Resets necessary properties to default values after each render step
  virtual void Reset() = 0;
};

}

#endif //ENGINE_INCLUDE_SPRITE_RENDERER_H_
