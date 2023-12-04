#ifndef SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_CONTENT_H_
#define SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_CONTENT_H_

#include "entities/ui/ui_text.h"
#include "common/definitions.h"
#include "engine/engine_config.h"

using namespace engine::entities;

namespace slime_shooter {

class PopupContent : public UiText {
 public:
  PopupContent() {
    GetTransform()->SetScale(0.75);
    SetColor(GameColor::Ui::TextWhite);

    SetContent(".");
    SetFont(GameFont::Default, 16);
    SetName("popup_content");
  }

  void UpdateContent(const std::string& content, Vector2d position) {
    SetContent(content);
    GetTransform()->Position = position;
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_CONTENT_H_
