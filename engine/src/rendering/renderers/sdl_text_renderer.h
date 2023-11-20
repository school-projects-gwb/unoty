#ifndef ENGINE_SRC_RENDERING_RENDERERS_SDL_TEXT_RENDERER_H_
#define ENGINE_SRC_RENDERING_RENDERERS_SDL_TEXT_RENDERER_H_

#include <SDL_ttf.h>
#include "rendering/text_renderer.h"
#include "sdl_renderer.h"
#include "map"

namespace engine::ui {

class SdlTextRenderer : public TextRenderer {
 public:
  void Init(void* renderer, int window_width, int window_height) override;
  void RenderText(TextRenderInfo& text_render_info) override;
 private:
  SdlRenderer* sdl_renderer_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  int window_width_;
  int window_height_;

  entities::Point GetCalculatedPosition(entities::ElementPosition position, entities::Point wrapper_size) const;
  void RenderText(SDL_Texture* text_texture, SDL_Rect position);
};

}

#endif //ENGINE_SRC_RENDERING_RENDERERS_SDL_TEXT_RENDERER_H_
