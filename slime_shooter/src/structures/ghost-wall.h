
#ifndef SLIME_SHOOTER_SRC_STRUCTURES_GHOST_WALL_H
#define SLIME_SHOOTER_SRC_STRUCTURES_GHOST_WALL_H

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"

using namespace engine::entities;

namespace slime_shooter  {

class GhostWall : public GameObject {
 public:
  explicit GhostWall(Point size, Vector2d position) {
    auto wall_sprite = Component::Create<Sprite>("resources/sprites/world/square.png");
    wall_sprite->SetOffset({(size.x / -2), (size.y / -2)});

    GetTransform()->Position = position;
    GetTransform()->SetSize(size);
    GetTransform()->SetScale(1.25f);

    AddComponent(wall_sprite);

    SetTagName("ghost_wall");
  }
};

}

#endif //SLIME_SHOOTER_SRC_STRUCTURES_GHOST_WALL_H
