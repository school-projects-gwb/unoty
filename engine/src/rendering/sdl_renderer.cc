#include <iostream>
#include "sdl_renderer.h"
#include "textures/texture_registry.h"
#include "entities/transform.h"
#include "helpers/debug.h"
#include "entities/sprite.h"
#include "entities/structs/sprite_flip.h"

namespace engine::ui {

SdlRenderer::SdlRenderer(int window_width, int window_height, const std::string& window_title) : window_(nullptr), renderer_(nullptr) {
  window_width_ = window_width;
  window_height_ = window_height;
  window_title_ = window_title;
  InitSdl();
}

void SdlRenderer::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow(window_title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               window_width_, window_height_, 0);
    if (!window_) std::cerr << "SDL window creation failed: " << SDL_GetError() << std::endl;

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) std::cerr << "SDL renderer creation failed: " << SDL_GetError() << std::endl;
  }
}

SdlRenderer::~SdlRenderer() {
  if (renderer_) SDL_DestroyRenderer(renderer_);
  if (window_) SDL_DestroyWindow(window_);
  SDL_Quit();
}

void SdlRenderer::SetBackgroundRenderColor(entities::Color background_color) {
  background_render_color_ = background_color;
}

void SdlRenderer::StartRenderFrame() {
  SDL_RenderClear(renderer_);
  SDL_SetRenderDrawColor(renderer_, background_render_color_.r, background_render_color_.g,
                         background_render_color_.b, background_render_color_.a);
}

void SdlRenderer::EndRenderFrame() {
  SDL_RenderPresent(renderer_);
}

void SdlRenderer::RenderSpriteWithColorOverlay(const std::string& sprite_path,
                                               const std::shared_ptr<entities::Transform> transform,
                                               entities::Color color, entities::SpriteFlip flip) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(sprite_path));
  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

  RenderSprite(sprite_path, transform, flip);

  SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void SdlRenderer::RenderSprite(const std::string& sprite_path, const std::shared_ptr<entities::Transform> transform,
                               entities::SpriteFlip flip) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(sprite_path));

  auto scaled_size = GetScaledSize(transform->GetScale());
  RenderTexture(texture, nullptr, transform->Position, scaled_size.x, scaled_size.y, flip, transform->GetRotation());
}

void SdlRenderer::RenderSpriteFromSheet(const std::string &sprite_path, const std::shared_ptr<entities::Transform> transform,
                                        const entities::Rectangle& position_in_sheet, entities::SpriteFlip flip) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(sprite_path));

  SDL_Rect sheet_rectangle = GetSheetRectangle(position_in_sheet);
  auto scaled_size = GetScaledSize(transform->GetScale());
  RenderTexture(texture, &sheet_rectangle, transform->Position, scaled_size.x,
                scaled_size.y, flip, transform->GetRotation());
}

void SdlRenderer::RenderSpriteFromSheetWithColorOverlay(const std::string &sprite_path, const std::shared_ptr<entities::Transform> transform,
                                        const entities::Rectangle& position_in_sheet, entities::Color color,
                                        entities::SpriteFlip flip) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(sprite_path));

  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

  SDL_Rect sheet_rectangle = GetSheetRectangle(position_in_sheet);
  auto scaled_size = GetScaledSize(transform->GetScale());
  RenderTexture(texture, &sheet_rectangle, transform->Position, scaled_size.x,
                scaled_size.y, flip, transform->GetRotation());

  SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void SdlRenderer::RenderSpriteFromSheet(const std::string &sprite_path, const entities::Rectangle& target_position,
                                        const entities::Rectangle& position_in_sheet) {
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(sprite_path));

  SDL_Rect sheet_rectangle = GetSheetRectangle(position_in_sheet);

  RenderTexture(texture, &sheet_rectangle, {target_position.x, target_position.y},
                target_position.w, target_position.h, entities::SpriteFlip::FlipNone);
}

SDL_Rect SdlRenderer::GetSheetRectangle(const entities::Rectangle& position_in_sheet) {
  SDL_Rect sheet_rectangle;
  sheet_rectangle.x = position_in_sheet.x * position_in_sheet.w;
  sheet_rectangle.y = position_in_sheet.y * position_in_sheet.h;
  sheet_rectangle.w = position_in_sheet.w;
  sheet_rectangle.h = position_in_sheet.h;

  return sheet_rectangle;
}

void SdlRenderer::RenderTexture(SDL_Texture* texture, const SDL_Rect* source_rect,
                                const entities::Point& destination_position, int width, int height,
                                entities::SpriteFlip flip, double rotation) const {
  SDL_Rect destination_rectangle;
  destination_rectangle.x = destination_position.x - camera_position_.x - (width/2);
  destination_rectangle.y = destination_position.y - camera_position_.y - (height/2);
  destination_rectangle.w = width;
  destination_rectangle.h = height;

  auto sdl_flip = GetSdlRendererFlipFromSpriteFlip(flip);

  SDL_RenderCopyEx(renderer_, texture, source_rect, &destination_rectangle, rotation,
                   {}, sdl_flip);
}

SDL_RendererFlip SdlRenderer::GetSdlRendererFlipFromSpriteFlip(entities::SpriteFlip sprite_flip) {
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

entities::Point SdlRenderer::GetScaledSize(float scale) const {
  int width = kDefaultSpriteWidth * scale;
  int height = kDefaultSpriteHeight * scale;

  return {width, height};
}

void *SdlRenderer::GetRenderer() {
  return renderer_;
}

void SdlRenderer::Exit() {
  SDL_Quit();
}

void SdlRenderer::UpdateCameraPosition(engine::entities::Camera* camera) {
  // Get position camera is tracking
  auto center_target_position = camera->GetTransform()->Position;
  if (center_target_position.x == 0 && center_target_position.y == 0) return; // Assume static camera position

  // Calculate and set camera position; center it around target position
  int camera_x = center_target_position.x - (window_width_ / 2);
  int camera_y = center_target_position.y - (window_height_ / 2);

  camera_position_.x = camera_x;
  camera_position_.y = camera_y;
}

}