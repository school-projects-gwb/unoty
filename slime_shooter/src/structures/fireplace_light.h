#ifndef SLIME_SHOOTER_SRC_PLAYER_BASE_SLIME_SHOOTER_SRC_PLAYER_BASE_FIREPLACE_LIGHT_H_
#define SLIME_SHOOTER_SRC_PLAYER_BASE_SLIME_SHOOTER_SRC_PLAYER_BASE_FIREPLACE_LIGHT_H_

#include "entities/game_object.h"
#include "entities/light_source.h"

using namespace engine::entities;

namespace slime_shooter {

class FireplaceLight : public GameObject {
 public:
  FireplaceLight() {
    auto light = Component::Create<LightSource>("resources/sprites/light_sources/yellow.png");
    light->GetSprite().SetColor({255, 149, 110});
    AddComponent(light);

    GetTransform()->SetSize({700, 700});
    SetName("FireplaceLight");
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_BASE_SLIME_SHOOTER_SRC_PLAYER_BASE_FIREPLACE_LIGHT_H_
