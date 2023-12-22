#ifndef SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_BED_OBJECT_H_
#define SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_BED_OBJECT_H_

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"

using namespace engine::entities;

namespace slime_shooter  {

class BedObject : public GameObject {
 public:
  BedObject() {
    auto background_object_sprite = Component::Create<Sprite>("resources/sprites/world/bed.png");
    AddComponent(background_object_sprite);
    GetTransform()->Position = {450, 415};
    GetTransform()->SetScale(2.7);
  }
};

}

#endif //SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_BED_OBJECT_H_
