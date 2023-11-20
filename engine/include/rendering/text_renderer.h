#ifndef ENGINE_INCLUDE_RENDERING_ENGINE_INCLUDE_RENDERING_TEXT_RENDERER_H_
#define ENGINE_INCLUDE_RENDERING_ENGINE_INCLUDE_RENDERING_TEXT_RENDERER_H_

#include "entities/structs/point.h"
#include "string"
#include "entities/structs/element_position.h"
#include "entities/structs/color.h"

namespace engine::ui {

struct TextRenderInfo {
  std::string font_path;
  int font_size;
  std::string content;
  entities::Point target_position;
  entities::ElementPosition element_position = entities::ElementPosition::CustomPosition;
  entities::Color text_color = {255, 255, 255, 255};
};

class TextRenderer {
 public:
  virtual ~TextRenderer() = default;

  virtual void Init(void* renderer, int window_width, int window_height) = 0;

  virtual void RenderText(TextRenderInfo& text_render_info) = 0;
};

}

#endif //ENGINE_INCLUDE_RENDERING_ENGINE_INCLUDE_RENDERING_TEXT_RENDERER_H_
