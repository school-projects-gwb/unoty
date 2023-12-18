#ifndef ENGINE_SRC_UI_SDL_RENDERER_H_
#define ENGINE_SRC_UI_SDL_RENDERER_H_

#include <SDL.h>
#include <SDL_image.h>
#include "rendering/renderer.h"
#include "entities/transform.h"
#include "entities/component.h"
#include "entities/camera.h"
#include "entities/structs/rectangle.h"
#include "entities/sprite.h"

namespace engine::ui {

/// @brief SDL renderer implementation
class SdlRenderer : public Renderer {
 public:
  SdlRenderer(int window_width, int window_height, const std::string& window_title);
  ~SdlRenderer() override;

  void SetBackgroundRenderColor(entities::Color background_color) override;

  void StartRenderFrame() override;
  void EndRenderFrame() override;

  void Exit() override;
  void* GetRenderer() override;
  std::unique_ptr<SpriteRenderer>& GetSpriteRenderer() override;
  std::unique_ptr<TextRenderer>& GetTextRenderer() override;

  void UpdateCameraPosition(engine::entities::Camera* camera) override;

  [[nodiscard]] const entities::Point& GetCameraPosition() const;

  SDL_Rect &GetGameRect() {
    return game_rect_;
  }
 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  int window_width_;
  int window_height_;
  std::string window_title_;
  std::unique_ptr<SpriteRenderer> sprite_renderer_;
  std::unique_ptr<TextRenderer> text_renderer_;

  entities::Point camera_position_ = {0, 0};
  entities::Color background_render_color_ = {0, 0, 0};

  SDL_Rect game_rect_;

  void InitSdl();
};

}

#endif //ENGINE_SRC_UI_SDL_RENDERER_H_
