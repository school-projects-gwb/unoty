#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_SCORE_TEXT_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_SCORE_TEXT_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_text.h"

using namespace engine::entities;

namespace slime_shooter {

class ScoreText : public UiText {
 public:
  ScoreText() {
    GetTransform()->Position = {engine::EngineConfig::window_width/2 - 60, 25};
    GetTransform()->SetScale(0.75);
    SetColor(GameColor::Purple::Shade2);

    SetContent("SCORE: 0");
    SetFont("resources/fonts/PressStart2P-Regular.ttf", 16);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_SCORE_TEXT_H_
