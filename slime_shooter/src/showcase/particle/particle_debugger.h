#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_PARTICLE_DEBUGGER_H
#define SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_PARTICLE_DEBUGGER_H

#include <utility>

#include "entities/listeners/key_listener.h"
#include "engine/engine.h"
using namespace engine::entities;

namespace slime_shooter {

class ParticleDebugger : public KeyListener {
 public:
  explicit ParticleDebugger(std::shared_ptr<StressEmitter> stress_emitter)
      : KeyListener(), stress_emitter_(std::move(stress_emitter)) {
  }

 private:
  std::shared_ptr<StressEmitter> stress_emitter_;

  void OnKeyPressed() override {
    if (Input::HasPressedKey(Key::UnoSpace)) {
        auto firework_emitter = stress_emitter_->GetComponentByType<FireworkEmitter>();
        if(firework_emitter){
          firework_emitter->Start();
        }
    }

    if (Input::HasPressedKey(Key::UnoP)) {
      engine::Engine::GetInstance().SetActiveScene("menu_scene");
    }
  }
};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_PARTICLE_DEBUGGER_H
