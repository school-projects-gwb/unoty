#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_TURRET_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_TURRET_H_

#include "entities/game_object.h"
#include "string"
#include "entities/sprite.h"
#include "player_weapon_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class PlayerTurret : public GameObject {
 public:
  PlayerTurret() {
    auto sprite = Component::Create<Sprite>("resources/sprites/player/player_turret.png");
    AddComponent(sprite);

    GetTransform()->SetSize({200, 200});
    SetLayer(1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_TURRET_H_
