#ifndef ENGINE_SRC_RENDERING_TEXTURES_SDL_TEXTURE_REGISTRY_H_
#define ENGINE_SRC_RENDERING_TEXTURES_SDL_TEXTURE_REGISTRY_H_

#include <SDL_render.h>
#include <string>
#include <map>
#include "texture_registry_base.h"
#include <SDL_image.h>

namespace engine::rendering {

/// @brief Singleton Registry for SDL textures so that they can be created once and reused throughout each render frame
class SdlTextureRegistry : public TextureRegistryBase {
 public:
  static SdlTextureRegistry& GetInstance();
  SdlTextureRegistry(const SdlTextureRegistry&) = delete;
  ~SdlTextureRegistry() override;

  /// @brief Returns texture based on given image_path, creates new one if texture is not found
  void* GetTexture(const std::string& image_path) override;

  /// @brief Sets renderer by statically casting it to SDL_Renderer
  static void SetRenderer(std::unique_ptr<ui::Renderer> &renderer);
 private:
  SdlTextureRegistry();
  SdlTextureRegistry& operator=(const SdlTextureRegistry&) = delete;

  SDL_Renderer* renderer_;
  std::map<std::string, SDL_Texture*> texture_registry;

  /// @brief Loads image and registers texture from given image path if it does not yet exist
  void* RegisterTexture(const std::string& image_path) override;
};


}

#endif //ENGINE_SRC_RENDERING_TEXTURES_SDL_TEXTURE_REGISTRY_H_
