#ifndef DEBUG_APP__MOVEMENT_SCRIPT_H_
#define DEBUG_APP__MOVEMENT_SCRIPT_H_

#include <iostream>
#include "entities/behaviour_script.h"
#include "entities/game_object.h"

using namespace engine::entities;

class MovementScript : public BehaviourScript {
  void OnInput(const Key& key) override {
    auto game_object = GetGameObject();
    auto transform = game_object->GetTransform();

    switch (key) {
      case Key::Up:
        transform->Position.y -= 10;
        break;
      case Key::Down:
        transform->Position.y += 10;
        break;
      case Key::Left:
        transform->Position.x -= 10;
        break;
      case Key::Right:
        transform->Position.x += 10;
        break;
      default:
        break;
    }
  }
};

#endif //DEBUG_APP__MOVEMENT_SCRIPT_H_
