#ifndef SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_
#define SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_

#include "engine/engine.h"
#include "iostream"
#include "entities/listeners/key_listener.h"

using namespace engine::entities;

namespace slime_shooter {

class DebugToggleScript : public KeyListener {
  void OnKeyPressed() override {
    if (Input::HasPressedKey(Key::UnoZ))
      engine::Engine::GetInstance().ToggleDebugMode();
  }
};

}

#endif //SLIME_SHOOTER_SLIME_SHOOTER_DEBUG_TOGGLE_SCRIPT_H_
