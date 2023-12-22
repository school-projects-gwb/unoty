#ifndef ENGINE_SRC_RENDERING_ENGINE_SRC_RENDERING_SDL_SPRITE_RENDERER_H_
#define ENGINE_SRC_RENDERING_ENGINE_SRC_RENDERING_SDL_SPRITE_RENDERER_H_

#include <SDL.h>
#include <SDL_image.h>
#include "rendering/renderer.h"
#include "entities/transform.h"
#include "entities/component.h"
#include "entities/camera.h"
#include "entities/structs/rectangle.h"
#include "entities/sprite.h"
#include "sdl_renderer.h"

namespace engine::ui {

class SdlSpriteRenderer : public ui::SpriteRenderer {
 public:
  void Init(void *renderer, int window_width, int window_height) override;
  ~SdlSpriteRenderer();

  void RenderRectangle(const RenderInfo &render_info, const RenderOptions &render_options) override;

  void RenderSprite(const RenderInfo &render_info, const RenderOptions &render_options) override;
  void RenderSpriteWithColorOverlay(const RenderInfo &render_info, const RenderOptions &render_options) override;

  void RenderStaticSpriteFromSheet(const RenderInfo &render_info, const RenderOptions &render_options) override;
  void RenderSpriteFromSheet(const RenderInfo &render_info, const RenderOptions &render_options) override;
  void RenderSpriteFromSheetWithColorOverlay(const RenderInfo &render_info,
                                             const RenderOptions &render_options) override;

  void StartLightLayer(const entities::Color &lighting_color) override;

  void StartRenderFrame() override;
  void EndRenderFrame() override;
  void Reset() override;
 private:
  SDL_Texture *background_layer_;
  SDL_Texture *light_layer_;
  SDL_Texture *result_layer_;

  SdlRenderer *sdl_renderer_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  const int kDefaultSpriteWidth = 100;
  const int kDefaultSpriteHeight = 100;
  int window_width_;
  int window_height_;
  
  void RenderTexture(SDL_Texture *texture,
                     const SDL_Rect *source_rect,
                     const entities::Vector2d &destination_position,
                     entities::Point size,
                     entities::Point offset,
                     entities::SpriteFlip flip,
                     double rotation,
                     bool is_position_fixed,
                     bool is_ui_object) const;

  static SDL_RendererFlip GetSdlRendererFlipFromSpriteFlip(entities::SpriteFlip sprite_flip);

  static SDL_Rect GetSheetRectangle(const entities::structs::Rectangle &position_in_sheet);
  entities::Point GetScaledSize(float scale, entities::Point size) const;

  void RenderDebugRectangles(const std::vector<std::pair<entities::Vector2d,
                                                         entities::Vector2d>> &debug_rectangles) override;
};

}

#endif //ENGINE_SRC_RENDERING_ENGINE_SRC_RENDERING_SDL_SPRITE_RENDERER_H_
