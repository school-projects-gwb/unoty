#ifndef ENGINE_INCLUDE_ENGINE_RENDERER_H_
#define ENGINE_INCLUDE_ENGINE_RENDERER_H_

#include "entities/camera.h"
#include "entities/structs/rectangle.h"
#include "entities/structs/sprite_flip.h"

namespace engine::ui {

/// @brief Renderer class used to manage Render window and render contents
class Renderer {
 public:
  virtual ~Renderer() = default;

  /// @brief Sets color of all visible parts of the window where nothing is rendered
  virtual void SetBackgroundRenderColor(entities::Color background_color) = 0;

  /// @brief Starts frame; clears current frame and sets background color
  virtual void StartRenderFrame() = 0;

  /// @brief Ends frame; presents all data that should be rendered in current frame to window
  virtual void EndRenderFrame() = 0;

  /// @brief Renders basic sprite based on path and positional information in Transform
  virtual void RenderSprite(const std::string& sprite_path, std::shared_ptr<entities::Transform> transform,
                            entities::SpriteFlip flip) = 0;

  /// @overload Renders basic sprite with color modulation
  virtual void RenderSpriteWithColorOverlay(const std::string& sprite_path,
                                            const std::shared_ptr<entities::Transform> transform, entities::Color color,
                                            entities::SpriteFlip flip) = 0;

  /// @brief Renders sprite from sheet with all the same options as RenderSprite
  virtual void RenderSpriteFromSheet(const std::string &sprite_path, const std::shared_ptr<entities::Transform> transform,
                                     const entities::Rectangle &position_in_sheet, entities::SpriteFlip flip) = 0;

  /// @overload Renders sprite from sheet with all the same options as RenderSprite including a Color Overlay
  virtual void RenderSpriteFromSheetWithColorOverlay(const std::string &sprite_path, const std::shared_ptr<entities::Transform> transform,
                                                     const entities::Rectangle &position_in_sheet, entities::Color color,
                                                     entities::SpriteFlip flip) = 0;

  /// @brief Renders simple sprite from sheet without additional logic for rotation, flip, scaling etc.
  ///
  /// Used for i.e. static tile map rendering
  /// @overload
  virtual void RenderSpriteFromSheet(const std::string& sprite_path, const entities::Rectangle& target_position,
                                     const entities::Rectangle& position_in_sheet) = 0;

  /// @brief Exists Renderer; makes sure everything is shut down correctly
  virtual void Exit() = 0;

  virtual void UpdateCameraPosition(engine::entities::Camera* camera) = 0;

  virtual void* GetRenderer() = 0;
};

}

#endif //ENGINE_INCLUDE_ENGINE_RENDERER_H_
