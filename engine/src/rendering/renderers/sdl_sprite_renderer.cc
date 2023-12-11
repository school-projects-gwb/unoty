#include "sdl_sprite_renderer.h"
#include "rendering/textures/texture_registry.h"
#include "sdl_renderer.h"

namespace engine::ui {

void SdlSpriteRenderer::Init(void* renderer, int window_width, int window_height) {
  sdl_renderer_ = static_cast<SdlRenderer*>(renderer);
  renderer_ = static_cast<SDL_Renderer*>(sdl_renderer_->GetRenderer());
  window_width_ = window_width;
  window_height_ = window_height;
}

void SdlSpriteRenderer::RenderRectangle(const RenderInfo &render_info, const RenderOptions &render_options) {
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, render_options.color.r, render_options.color.g, render_options.color.b, render_options.color.a);

  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

  SDL_Rect rectangle;
  rectangle.x = render_info.target_position.x;
  rectangle.y = render_info.target_position.y;
  rectangle.w = render_info.target_position.w;
  rectangle.h = render_info.target_position.h;

  SDL_RenderFillRect(renderer_, &rectangle);
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_NONE);
}

void SdlSpriteRenderer::RenderSpriteWithColorOverlay(const RenderInfo& render_info, const RenderOptions& render_options) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(render_info.sprite_path));
  SDL_SetTextureColorMod(texture, render_options.color.r, render_options.color.g, render_options.color.b);

  RenderSprite(render_info, {render_options.flip});

  SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void SdlSpriteRenderer::RenderSprite(const RenderInfo& render_info, const RenderOptions& render_options) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(render_info.sprite_path));

  auto scaled_size = GetScaledSize(render_info.transform->GetScale(), render_info.size);
  RenderTexture(texture, nullptr, render_info.transform->Position, scaled_size.x,
                scaled_size.y, render_options.flip, render_info.transform->GetRotation(), render_options.is_position_fixed);
}

void SdlSpriteRenderer::RenderSpriteFromSheet(const RenderInfo& render_info, const RenderOptions& render_options) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(render_info.sprite_path));

  SDL_Rect sheet_rectangle = GetSheetRectangle(render_info.position_in_sheet);
  auto scaled_size = GetScaledSize(render_info.transform->GetScale(), render_info.size);
  RenderTexture(texture, &sheet_rectangle, render_info.transform->Position, scaled_size.x,
                scaled_size.y, render_options.flip, render_info.transform->GetRotation());
}

void SdlSpriteRenderer::RenderSpriteFromSheetWithColorOverlay(const RenderInfo& render_info, const RenderOptions& render_options) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(render_info.sprite_path));

  SDL_SetTextureColorMod(texture, render_options.color.r, render_options.color.g, render_options.color.b);

  SDL_Rect sheet_rectangle = GetSheetRectangle(render_info.position_in_sheet);
  auto scaled_size = GetScaledSize(render_info.transform->GetScale(), render_info.size);
  RenderTexture(texture, &sheet_rectangle, render_info.transform->Position, scaled_size.x,
                scaled_size.y, render_options.flip, render_info.transform->GetRotation());

  SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void SdlSpriteRenderer::RenderStaticSpriteFromSheet(const RenderInfo& render_info, const RenderOptions& render_options) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(render_info.sprite_path));

  SDL_Rect sheet_rectangle = GetSheetRectangle(render_info.position_in_sheet);

  RenderTexture(texture, &sheet_rectangle, {render_info.target_position.x, render_info.target_position.y},
                render_info.target_position.w, render_info.target_position.h, entities::FlipNone);
}

SDL_Rect SdlSpriteRenderer::GetSheetRectangle(const entities::structs::Rectangle& position_in_sheet) {
  SDL_Rect sheet_rectangle;
  sheet_rectangle.x = position_in_sheet.x * position_in_sheet.w;
  sheet_rectangle.y = position_in_sheet.y * position_in_sheet.h;
  sheet_rectangle.w = position_in_sheet.w;
  sheet_rectangle.h = position_in_sheet.h;

  return sheet_rectangle;
}

void SdlSpriteRenderer::RenderTexture(SDL_Texture* texture, const SDL_Rect* source_rect,
                                const entities::Vector2d& destination_position, int width, int height,
                                entities::SpriteFlip flip, double rotation, bool is_position_fixed) const {
  SDL_Rect destination_rectangle;

  auto camera_position = sdl_renderer_->GetCameraPosition();
  destination_rectangle.x = destination_position.x - (is_position_fixed ? 0 : camera_position.x - (width/2));
  destination_rectangle.y = destination_position.y - (is_position_fixed ? 0 : camera_position.y - (height/2));
  destination_rectangle.w = width;
  destination_rectangle.h = height;

  auto sdl_flip = GetSdlRendererFlipFromSpriteFlip(flip);

  SDL_RenderCopyEx(renderer_, texture, source_rect, &destination_rectangle, rotation,
                   {}, sdl_flip);
}

SDL_RendererFlip SdlSpriteRenderer::GetSdlRendererFlipFromSpriteFlip(entities::SpriteFlip sprite_flip) {
  if (sprite_flip == entities::SpriteFlip::FlipNone) return SDL_FLIP_NONE;

  switch (sprite_flip) {
    case entities::SpriteFlip::FlipHorizontal:
      return SDL_FLIP_HORIZONTAL;
    case entities::SpriteFlip::FlipVertical:
      return SDL_FLIP_VERTICAL;
    case entities::SpriteFlip::FlipHorizontalAndVertical:
      return (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    default:
      return SDL_FLIP_NONE;
  }
}

entities::Point SdlSpriteRenderer::GetScaledSize(float scale, entities::Point size) const {
  int width = (size.x == 0 ? kDefaultSpriteWidth : size.x) * scale;
  int height = (size.y == 0 ? kDefaultSpriteHeight : size.y) * scale;

  return {width, height};
}

void SdlSpriteRenderer::RenderDebugRectangles(const std::vector<std::pair<entities::Vector2d,
                                              entities::Vector2d>> &debug_rectangles) {
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);  // Set color to white for borders

  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

  for (const auto& rect : debug_rectangles) {
    // Draw border
    SDL_Rect borderRect;
    auto camera_position = sdl_renderer_->GetCameraPosition();
    std::cout << rect.first.x << " " << rect.first.y << "\n";
    borderRect.x = rect.first.x - (camera_position.x - (rect.second.x/2));
    borderRect.y = rect.first.y - (camera_position.y - (rect.second.y/2));
    borderRect.w = rect.second.x;
    borderRect.h = rect.second.y;
    SDL_RenderDrawRect(renderer_, &borderRect);
  }

  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_NONE);
}

}