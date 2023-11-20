#ifndef ENGINE_INCLUDE_ENTITIES_UI_TEXT_H_
#define ENGINE_INCLUDE_ENTITIES_UI_TEXT_H_

#include "ui_object.h"

namespace engine::entities {

/// @brief UiObject - text
class UiText : public UiObject {
 public:
  UiText();
  ~UiText();

  void Render(const std::unique_ptr<ui::Renderer>& renderer) override;

  void SetContent(const std::string& content);
  const std::string& GetContent() const;

  void SetFont(const std::string& font_path, int font_size = 12);
  const std::string& GetFont() const;

  void SetAlignment(int alignment);
  int GetAlignment() const;

  void SetColor(entities::Color color);
  entities::Color GetColor() const;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_UI_TEXT_H_
