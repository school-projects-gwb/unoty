#ifndef SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_
#define SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"

using namespace engine::entities;

namespace slime_shooter  {

class FireplaceObject : public GameObject {
 public:
  FireplaceObject() {
    auto animator = Component::Create<Animator>("resources/sprites/world/fireplace.png", 3, Point{27, 37}, Point{3,1});
    animator->SetSpriteSheetAtIndex("resources/sprites/world/fireplace.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->Play(true);

    AddComponent(animator);
    GetTransform()->Position = {1140, 515};
    GetTransform()->SetSize({100, 150});
  }
};

}

#endif //SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_
