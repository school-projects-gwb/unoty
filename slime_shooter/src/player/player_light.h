#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_LIGHT_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_LIGHT_H_

#include "entities/game_object.h"
#include "string"
#include "entities/light_source.h"
#include "player_light_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class PlayerLight : public GameObject {
 public:
  PlayerLight() {
    auto light_source = Component::Create<LightSource>("resources/sprites/light_sources/yellow.png");
    auto player_light_logic = Component::Create<PlayerLightLogic>();

    AddComponent(light_source);
    AddComponent(player_light_logic);

    GetTransform()->SetSize({1100, 1100});
    SetLayer(1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_LIGHT_H_
