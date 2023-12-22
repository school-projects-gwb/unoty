#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_TURRET_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_TURRET_H_

#include "entities/game_object.h"
#include "string"
#include "entities/sprite.h"
#include "player_weapon_logic.h"
#include "entities/artificial_intelligence/circle_path_around_object_ai.h"
#include "player_turret_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class PlayerTurret : public GameObject {
 public:
  PlayerTurret() {
    auto sprite = Component::Create<Sprite>("resources/sprites/player/player_turret.png");
    AddComponent(sprite);

    auto circle_ai = Component::Create<CircleAroundObjectAI>();
    circle_ai->SetDistance(125.0f);
    circle_ai->SetSpeed(0.075f);
    AddComponent(circle_ai);

    auto script = Component::Create<TurretScript>();
    AddComponent(script);

    GetTransform()->SetSize({200, 200});
    SetLayer(1);
    SetName("player_turret");
    SetIsActive(false);
  }

  void Init() {
    auto circle_ai = GetComponentByType<CircleAroundObjectAI>();
    circle_ai->Init(GetParent());
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_TURRET_H_
