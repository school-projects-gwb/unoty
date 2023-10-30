#ifndef ENGINE_SRC_RENDERING_TEXTURES_TEXTURE_REGISTRY_BASE_H_
#define ENGINE_SRC_RENDERING_TEXTURES_TEXTURE_REGISTRY_BASE_H_

#include <SDL_render.h>
#include <string>
#include "engine/renderer.h"
namespace engine::rendering {

class TextureRegistryBase {
 public:
  virtual ~TextureRegistryBase() {}
  virtual void* RegisterTexture(const std::string& image_path) = 0;
  virtual void* GetTexture(const std::string& image_path) = 0;
};

}

#endif //ENGINE_SRC_RENDERING_TEXTURES_TEXTURE_REGISTRY_BASE_H_
