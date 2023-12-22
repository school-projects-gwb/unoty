#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_FIREWORK_H
#define SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_FIREWORK_H

#include "entities/game_object.h"
#include "entities/sprite.h"
#include "engine/engine_config.h"
#include "entities/particle_emitters/firework_emitter.h"

using namespace engine::entities;

namespace slime_shooter {

class Firework : public GameObject {
 public:
  Firework() {
    int amount = 30;
    int max_generation = 4;
    int distance = 180;

    auto firework_sprite = Component::Create<Sprite>("resources/sprites/world/particle_orange.png");
    auto firework_emitter = Component::Create<FireworkEmitter>(firework_sprite, amount, max_generation, distance);

    firework_emitter->SetLooping(true);
    firework_emitter->SetEmissionInterval(6);
    firework_emitter->SetDuration(1);

    GetTransform()->Position = {engine::EngineConfig::window_width / 2 + 100, engine::EngineConfig::window_height / 2};
    AddComponent(firework_emitter);
    firework_emitter->Start();
  }
};

}


#endif //SLIME_SHOOTER_SRC_SHOWCASE_PARTICLE_FIREWORK_H
