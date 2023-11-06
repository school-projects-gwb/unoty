#include <iostream>
#include <filesystem>
#include "sdl_texture_registry.h"
#include "helpers/path_helper.h"
#include "helpers/debug.h"

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

  // Texture not found; register new one
  if (it == texture_registry.end()) {
    std::string full_path = helpers::PathHelper::GetFullPathFromRelative(image_path);
    const char* image_path_c_str = full_path.c_str();

    // Loads image into memory
    SDL_Surface* image_surface = IMG_Load(image_path_c_str);

    if (!image_surface) {
      helpers::Debug::Error("Image not found at path: " + full_path);
      return nullptr;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, image_surface);

    // The surface can be freed again since we no longer require it
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

void SdlTextureRegistry::SetRenderer(std::unique_ptr<ui::Renderer> &renderer) {
  GetInstance().renderer_ = static_cast<SDL_Renderer*>(renderer->GetRenderer());
}

}