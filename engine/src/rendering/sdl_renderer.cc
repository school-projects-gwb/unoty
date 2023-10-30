#include <iostream>
#include "sdl_renderer.h"
#include "textures/texture_registry.h"
#include "entities/transform.h"

namespace engine::ui {

SdlRenderer::SdlRenderer(int window_width, int window_height) : window_(nullptr), renderer_(nullptr) {
  window_width_ = window_width;
  window_height_ = window_height;
  InitSdl();
}

void SdlRenderer::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width_, window_height_, 0);
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

void SdlRenderer::RenderSprite(const std::string& sprite_path, const entities::Point& position) {
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderClear(renderer_);
  auto* texture = static_cast<SDL_Texture *>(rendering::TextureRegistry::GetInstance().GetTexture(sprite_path));

  SDL_Rect destination_rectangle;
  destination_rectangle.x = position.x;
  destination_rectangle.y = position.y;
  destination_rectangle.w = 100;
  destination_rectangle.h = 100;

  SDL_RenderCopy(renderer_, texture, NULL, &destination_rectangle);

  SDL_RenderPresent(renderer_);
}

void SdlRenderer::RenderSpriteFromSheet(const std::string &sprite_path, const entities::Point &position,
                                        const entities::Point &size) {
// @todo implement
// same as RenderSprite but including position in and size of the sprite in the texture
}

void *SdlRenderer::GetRenderer() {
  return renderer_;
}

void SdlRenderer::UpdateCameraPosition(engine::entities::Camera* camera) {
  // todo compare and add support vor PreviousPosition so that we can skip this logic if it's the same
  entities::Point cameraPosition = camera->GetTransform().Position;

  SDL_RenderSetViewport(renderer_, NULL);
  SDL_Rect camera_rectangle;
  camera_rectangle.x = 0 - cameraPosition.x;
  camera_rectangle.y = 0 - cameraPosition.y;
  camera_rectangle.w = window_width_;
  camera_rectangle.h = window_height_;
  SDL_RenderSetViewport(renderer_, &camera_rectangle);
}

}