#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_LIGHT_H_
#define SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_LIGHT_H_

#include "entities/game_object.h"
#include "string"
#include "entities/light_source.h"
#include "player_light_logic.h"

using namespace engine::entities;

namespace slime_shooter::showcase {

class PlayerLight : public GameObject {
 public:
  PlayerLight() {
    auto light_source = Component::Create<LightSource>("resources/sprites/light_sources/yellow.png");
    light_source->GetSprite().SetColor({254, 254, 254, 255});
    auto player_light_logic = Component::Create<showcase::PlayerLightLogic>();

    AddComponent(light_source);
    AddComponent(player_light_logic);

    GetTransform()->SetSize({500, 500});
    SetLayer(1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_LIGHT_H_
