#ifndef SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_TITLE_H_
#define SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_TITLE_H_

#include "entities/ui/ui_text.h"
#include "common/definitions.h"
#include "engine/engine_config.h"

using namespace engine::entities;

namespace slime_shooter {

class PopupTitle : public UiText {
 public:
  PopupTitle() {
    GetTransform()->SetScale(0.75);
    SetColor(GameColor::Ui::TextGreen);

    SetContent(".");
    SetFont(GameFont::Default, 36);
    SetName("popup_title");
  }

  void UpdateContent(const std::string& content, Vector2d position) {
    SetContent(content);
    GetTransform()->Position= position;
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_POPUP_SLIME_SHOOTER_SRC_UI_POPUP_POPUP_TITLE_H_
