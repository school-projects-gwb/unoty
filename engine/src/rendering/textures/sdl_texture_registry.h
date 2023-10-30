#ifndef ENGINE_SRC_RENDERING_TEXTURES_SDL_TEXTURE_REGISTRY_H_
#define ENGINE_SRC_RENDERING_TEXTURES_SDL_TEXTURE_REGISTRY_H_

#include <SDL_render.h>
#include <string>
#include <map>
#include "texture_registry_base.h"
#include <SDL_image.h>

namespace engine::rendering {

class SdlTextureRegistry : public TextureRegistryBase {
 public:
  static SdlTextureRegistry& GetInstance();
  ~SdlTextureRegistry();

  void* RegisterTexture(const std::string& image_path) override;
  void* GetTexture(const std::string& image_path) override;
  static void Initialize(std::unique_ptr<ui::Renderer> &renderer);
 private:
  SdlTextureRegistry();
  SdlTextureRegistry(const SdlTextureRegistry&) = delete;
  SdlTextureRegistry& operator=(const SdlTextureRegistry&) = delete;

  SDL_Renderer* renderer_;
  std::map<std::string, SDL_Texture*> texture_registry;
};


}

#endif //ENGINE_SRC_RENDERING_TEXTURES_SDL_TEXTURE_REGISTRY_H_
