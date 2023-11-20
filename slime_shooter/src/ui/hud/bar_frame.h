#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_BAR_FRAME_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_BAR_FRAME_H_

#include "entities/ui/ui_object.h"
#include "engine/engine_config.h"

using namespace engine::entities;

namespace slime_shooter {

class BarFrame : public UiObject {
 public:
  BarFrame() {
    GetTransform()->SetScale(3);
    SetSpritePath("resources/sprites/ui/bar.png");
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_BAR_FRAME_H_
