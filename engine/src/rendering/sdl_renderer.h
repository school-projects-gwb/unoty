#ifndef ENGINE_SRC_UI_SDL_RENDERER_H_
#define ENGINE_SRC_UI_SDL_RENDERER_H_

#include <SDL.h>
#include <SDL_image.h>
#include "engine/renderer.h"
#include "entities/transform.h"
#include "entities/component.h"
#include "entities/camera.h"
#include "entities/structs/rectangle.h"
#include "entities/sprite.h"

namespace engine::ui {

/// @brief SDL renderer implementation
class SdlRenderer : public Renderer {
 public:
  SdlRenderer(int window_width, int window_height, const std::string& window_title);
  ~SdlRenderer() override;

  void SetBackgroundRenderColor(entities::Color background_color) override;
  void StartRenderFrame() override;
  void EndRenderFrame() override;

  void RenderSpriteWithColorOverlay(const std::string& sprite_path, const std::shared_ptr<entities::Transform> transform,
                                    entities::Color color, entities::SpriteFlip flip) override;
  void RenderSprite(const std::string& sprite_path, std::shared_ptr<entities::Transform> transform,
                    entities::SpriteFlip flip) override;
  void RenderSpriteFromSheet(const std::string& sprite_path, const entities::Rectangle& target_position,
                             const entities::Rectangle& position_in_sheet) override;
  void RenderSpriteFromSheet(const std::string &sprite_path, const std::shared_ptr<entities::Transform> transform,
                             const entities::Rectangle &position_in_sheet, entities::SpriteFlip flip) override;
  void RenderSpriteFromSheetWithColorOverlay(const std::string &sprite_path, const std::shared_ptr<entities::Transform> transform,
                             const entities::Rectangle &position_in_sheet, entities::Color color,
                             entities::SpriteFlip flip) override;

  void Exit() override;
  void UpdateCameraPosition(engine::entities::Camera* camera) override;
  void* GetRenderer() override;
 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  int window_width_;
  int window_height_;
  std::string window_title_;
  entities::Point camera_position_ = {0, 0};
  const int kDefaultSpriteWidth = 100;
  const int kDefaultSpriteHeight = 100;
  entities::Color background_render_color_ = {0, 0, 0};

  void InitSdl();
  void RenderTexture(SDL_Texture* texture, const SDL_Rect* source_rect, const entities::Point& destination_position,
                     int width, int height, entities::SpriteFlip flip, double rotation=0) const;
  static SDL_RendererFlip GetSdlRendererFlipFromSpriteFlip(entities::SpriteFlip sprite_flip) ;

  static SDL_Rect GetSheetRectangle(const entities::Rectangle &position_in_sheet);
  entities::Point GetScaledSize(float scale) const;
};

}

#endif //ENGINE_SRC_UI_SDL_RENDERER_H_
