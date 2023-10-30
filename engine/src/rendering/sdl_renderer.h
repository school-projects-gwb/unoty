#ifndef ENGINE_SRC_UI_SDL_RENDERER_H_
#define ENGINE_SRC_UI_SDL_RENDERER_H_

#include <SDL.h>
#include <SDL_image.h>
#include "engine/renderer.h"
#include "entities/transform.h"
#include "entities/component.h"
#include "entities/camera.h"

namespace engine::ui {

class SdlRenderer : public Renderer {
 public:
  SdlRenderer(int window_width, int window_height);
  ~SdlRenderer();
  void RenderSprite(const std::string& sprite_path, const entities::Point& position) override;
  void RenderSpriteFromSheet(const std::string& sprite_path, const entities::Point& position, const entities::Point& size) override;
  void UpdateCameraPosition(engine::entities::Camera* camera) override;
  void* GetRenderer() override;
 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  int window_width_;
  int window_height_;
  void InitSdl();
};

}

#endif //ENGINE_SRC_UI_SDL_RENDERER_H_
