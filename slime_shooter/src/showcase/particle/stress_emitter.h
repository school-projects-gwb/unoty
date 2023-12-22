#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_STRESS_EMITTER_H
#define SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_STRESS_EMITTER_H

#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/particle_emitters/firework_emitter.h"
#include "engine/engine_config.h"
using namespace engine::entities;

namespace slime_shooter {

class StressEmitter : public GameObject {
 public:
  std::shared_ptr<FireworkEmitter> firework_emitter_;

  StressEmitter() {
    SetName("StressEmitter");
    GetTransform()->Position = {engine::EngineConfig::window_width / 2, engine::EngineConfig::window_height / 2};

    int amount = 30;
    int max_generation = 5;
    int distance = 240;
    auto firework_sprite = Component::Create<Sprite>("resources/sprites/world/particle_orange.png");

    firework_emitter_ = Component::Create<FireworkEmitter>(firework_sprite, amount, max_generation, distance);
    firework_emitter_->SetLooping(false);
    firework_emitter_->SetEmissionInterval(6);
    firework_emitter_->SetDuration(1);

    AddComponent(firework_emitter_);
  }

};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_STRESS_EMITTER_H
