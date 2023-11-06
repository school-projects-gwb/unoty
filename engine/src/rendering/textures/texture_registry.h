#ifndef ENGINE_SRC_RENDERING_TEXTURES_TEXTURE_REGISTRY_H_
#define ENGINE_SRC_RENDERING_TEXTURES_TEXTURE_REGISTRY_H_

#include "texture_registry_base.h"
#include "sdl_texture_registry.h"
namespace engine::rendering {

class TextureRegistry {
 public:
  static TextureRegistryBase& GetInstance() {
    return SdlTextureRegistry::GetInstance();
  }

  static void Initialize(std::unique_ptr<ui::Renderer>& renderer) {
    SdlTextureRegistry::SetRenderer(renderer);
  }
};

}

#endif //ENGINE_SRC_RENDERING_TEXTURES_TEXTURE_REGISTRY_H_
