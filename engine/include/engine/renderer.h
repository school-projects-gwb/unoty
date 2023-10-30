#ifndef ENGINE_INCLUDE_ENGINE_RENDERER_H_
#define ENGINE_INCLUDE_ENGINE_RENDERER_H_

#include "entities/camera.h"

namespace engine::ui {

class Renderer {
 public:
  virtual ~Renderer() = default;
  virtual void UpdateCameraPosition(engine::entities::Camera* camera) = 0;
  virtual void RenderSprite(const std::string& sprite_path, const entities::Point& position) = 0;
  virtual void RenderSpriteFromSheet(const std::string& sprite_path, const entities::Point& position,
                                     const entities::Point& size) = 0;
  virtual void* GetRenderer() = 0;
};

}

#endif //ENGINE_INCLUDE_ENGINE_RENDERER_H_
