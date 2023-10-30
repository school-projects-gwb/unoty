#include <iostream>
#include "sdl_texture_registry.h"

namespace engine::rendering {

SdlTextureRegistry::SdlTextureRegistry() : renderer_(nullptr) {}

SdlTextureRegistry& SdlTextureRegistry::GetInstance() {
  static SdlTextureRegistry instance;
  return instance;
}

SdlTextureRegistry::~SdlTextureRegistry() {
  for (auto& pair : texture_registry) SDL_DestroyTexture(pair.second);
  texture_registry.clear();
}

void* SdlTextureRegistry::RegisterTexture(const std::string& image_path) {
  auto it = texture_registry.find(image_path);
  if (it == texture_registry.end()) {
    SDL_Surface* image_surface = IMG_Load(image_path.c_str());
    if (!image_surface) return nullptr;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, image_surface);
    SDL_FreeSurface(image_surface);

    if (texture) texture_registry[image_path] = texture;

    return texture;
  }

  return it->second;
}

void* SdlTextureRegistry::GetTexture(const std::string& image_path) {
  auto it = texture_registry.find(image_path);
  if (it != texture_registry.end()) return it->second;

  return RegisterTexture(image_path);
}

void SdlTextureRegistry::Initialize(std::unique_ptr<ui::Renderer> &renderer) {
  GetInstance().renderer_ = static_cast<SDL_Renderer*>(renderer->GetRenderer());
}

}