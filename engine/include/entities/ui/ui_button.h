#ifndef ENGINE_INCLUDE_ENTITIES_UI_BUTTON_H_
#define ENGINE_INCLUDE_ENTITIES_UI_BUTTON_H_

#include "ui_object.h"
#include "ui_button_callback_function.h"

namespace engine::entities {

/// @brief UiObject - button
class UiButton : public UiObject {
 public:
  explicit UiButton(entities::UiButtonCallbackFunction callback_function);
  ~UiButton();

  void Render(const std::unique_ptr<ui::Renderer>& renderer) override;

  void TriggerClick();

  void SetText(const std::string &text, const std::string &font_path, int font_size, entities::Color color);

  /// @brief Sets text position relative to button (background rectangle) position
  void SetRelativeTextPosition(entities::Point position);

  void SetBackgroundColor(entities::Color background_color) override;

  /// @brief Affects both button background and text element position
  void SetPosition(entities::Point position);

  /// @brief Affects only the size of the button background element
  void SetSize(entities::Point size);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_UI_BUTTON_H_
