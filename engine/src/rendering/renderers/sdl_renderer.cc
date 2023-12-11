#include <iostream>
#include "sdl_renderer.h"
#include "rendering/textures/texture_registry.h"
#include "entities/transform.h"
#include "utility/debug.h"
#include "entities/sprite.h"
#include "entities/structs/sprite_flip.h"
#include "sdl_sprite_renderer.h"
#include "sdl_text_renderer.h"

namespace engine::ui {

SdlRenderer::SdlRenderer(int window_width, int window_height, const std::string& window_title) : window_(nullptr), renderer_(nullptr) {
  window_width_ = window_width;
  window_height_ = window_height;
  window_title_ = window_title;
  sprite_renderer_ = std::make_unique<SdlSpriteRenderer>();
  text_renderer_ = std::make_unique<SdlTextRenderer>();

  InitSdl();
}

void SdlRenderer::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window_ = SDL_CreateWindow(window_title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               window_width_, window_height_, 0);
    if (!window_) std::cerr << "SDL window creation failed: " << SDL_GetError() << std::endl;

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) std::cerr << "SDL renderer creation failed: " << SDL_GetError() << std::endl;

    sprite_renderer_->Init(this, window_width_, window_height_);
    text_renderer_->Init(this, window_width_, window_height_);
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

void *SdlRenderer::GetRenderer() {
  return renderer_;
}

void SdlRenderer::Exit() {
  SDL_Quit();
}

std::unique_ptr<SpriteRenderer> &SdlRenderer::GetSpriteRenderer() {
  return sprite_renderer_;
}

std::unique_ptr<TextRenderer> &SdlRenderer::GetTextRenderer() {
  return text_renderer_;
}

void SdlRenderer::UpdateCameraPosition(engine::entities::Camera* camera) {
  // Get position camera is tracking
  auto center_target_position = camera->GetTransform()->Position;
  // TODO possibly improve this logic
  if (center_target_position.x == 0 && center_target_position.y == 0) {
    camera_position_.x = 0;
    camera_position_.y = 0;
    camera->SetPosition({0, 0});
    return;
  }

  auto target_transform = camera->GetTrackingTransform();

  // Calculate and set camera position; center it around target position
  int camera_x = (center_target_position.x + (target_transform->GetSize().x)) - (window_width_ / 2);
  int camera_y = (center_target_position.y + (target_transform->GetSize().y)) - (window_height_ / 2);

  camera_position_.x = camera_x;
  camera_position_.y = camera_y;

  camera->SetPosition({camera_x, camera_y});
}

const entities::Point& SdlRenderer::GetCameraPosition() const {
  return camera_position_;
}

}