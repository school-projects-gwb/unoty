#ifndef SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_BUTTON_CLICK_LISTENER_H_
#define SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_BUTTON_CLICK_LISTENER_H_

#include "engine/engine.h"
#include "iostream"
#include "entities/listeners/mouse_listener.h"
#include "entities/ui/ui_button.h"

using namespace engine::entities;

namespace slime_shooter {

class ButtonMouseClickListener : public MouseListener {
 public:
  void OnMouseClicked() override {
    if (!button_objects_set_) SetButtonObjects();

    auto click_position = Input::GetMousePointerPosition();
    Vector2d click_position_float = {click_position.x, click_position.y};

    for(auto game_object : button_objects_) {
      if (game_object->GetTransform()->IsInPositionBounds(click_position_float)) {
        auto button = GameObject::Cast<UiButton>(game_object);
        button->TriggerClick();
      }
    }
  }

  void SetButtonObjects() {
    button_objects_set_ = true;
    button_objects_ = GameObject::GetSceneObjectsByTagName("button", true);
  }

 private:
  bool button_objects_set_ = false;
  std::vector<std::shared_ptr<GameObject>> button_objects_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_SLIME_SHOOTER_SRC_UI_BUTTON_CLICK_LISTENER_H_
