#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_H_

#include "entities/game_object.h"
#include "string"
#include "entities/sprite.h"
#include "player_weapon_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class PlayerWeapon : public GameObject {
 public:
  PlayerWeapon() {
    auto sprite = Component::Create<Sprite>("resources/sprites/player/weapon.png");
    auto player_weapon_logic = Component::Create<PlayerWeaponLogic>();

    AddComponent(sprite);
    AddComponent(player_weapon_logic);

    GetTransform()->SetSize({65, 65});
    SetName("PlayerWeapon");
    SetLayer(1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_WEAPON_H_
