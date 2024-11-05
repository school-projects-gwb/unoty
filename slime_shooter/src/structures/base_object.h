#ifndef SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_BASE_OBJECT_H_
#define SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_BASE_OBJECT_H_

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "base_logic.h"

using namespace engine::entities;

namespace slime_shooter  {

class BaseObject : public GameObject {
 public:
  BaseObject() {
    auto base_object_sprite = Component::Create<Sprite>("resources/sprites/world/floor.png");
    AddComponent(base_object_sprite);
    GetTransform()->Position = {600, 500};
    GetTransform()->SetSize({700, 430});

    auto base_logic = GameObject::Create<BaseLogic>();
    AddComponent(base_logic);
  }
};

}

#endif //SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_BASE_OBJECT_H_
