#include "sdl_text_renderer.h"
#include "sdl_renderer.h"
#include "rendering/fonts/sdl_font_registry.h"
#include "utility/debug.h"

namespace engine::ui {

void SdlTextRenderer::Init(void* renderer, int window_width, int window_height) {
  sdl_renderer_ = static_cast<SdlRenderer*>(renderer);
  renderer_ = static_cast<SDL_Renderer*>(sdl_renderer_->GetRenderer());
  window_width_ = window_width;
  window_height_ = window_height;

  if (TTF_Init() == -1) {
    helpers::Debug::Error("Error: SDL_TTF could not be initialised.");
  }
}

void SdlTextRenderer::RenderText(TextRenderInfo& text_render_info) {
  auto font = SdlFontRegistry::GetFont(text_render_info.font_path, text_render_info.font_size);
  if (font == nullptr) return;

  SDL_Color text_color = {text_render_info.text_color.r, text_render_info.text_color.g, text_render_info.text_color.b};
  SDL_Surface* text_surface = TTF_RenderText_Solid(font, text_render_info.content.c_str(), text_color);

  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer_, text_surface);

  if (text_render_info.element_position != entities::CustomPosition) {
    auto calculated_position = GetCalculatedPosition(text_render_info.element_position,
                                                     {text_surface->w, text_surface->h});
    SDL_Rect destination_rect = {calculated_position.x, calculated_position.y, text_surface->w, text_surface->h};
    RenderText(text_texture, destination_rect);
  } else {
    SDL_Rect destination_rect = {text_render_info.target_position.x, text_render_info.target_position.y, text_surface->w, text_surface->h};
    RenderText(text_texture, destination_rect);
  }

  SDL_FreeSurface(text_surface);
}

void SdlTextRenderer::RenderText(SDL_Texture *text_texture, SDL_Rect destination_rectangle) {
  SDL_RenderCopy(renderer_, text_texture, nullptr, &destination_rectangle);
  SDL_DestroyTexture(text_texture);
}

entities::Point SdlTextRenderer::GetCalculatedPosition(entities::ElementPosition position,
                                                       entities::Point wrapper_size) const {
  // Very small edge distance so the text isn't exactly at the border of the window and still readable
  // TODO possibly make this user-configurable
  const int edge_distance = 5;

  switch (position) {
    case entities::TopLeft:
      return {edge_distance, edge_distance};
    case entities::TopRight:
      return {window_width_-wrapper_size.x-edge_distance, edge_distance};
      break;
    case entities::BottomLeft:
      return {edge_distance, window_height_-wrapper_size.y-edge_distance};
      break;
    case entities::BottomRight:
      return {window_width_-wrapper_size.x-edge_distance, window_height_-wrapper_size.y-edge_distance};
      break;
    default:
      return {0,0};
  }
}

}