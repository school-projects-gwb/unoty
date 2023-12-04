#ifndef SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_
#define SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "player_base/particle/smoke_emitter.h"

using namespace engine::entities;

namespace slime_shooter  {

class FireplaceObject : public GameObject {
 public:
  FireplaceObject() {
    auto animator = Component::Create<Animator>("resources/sprites/world/fireplace.png", 3, Point{27, 37}, Point{3,1});
    animator->SetSpriteSheetAtIndex("resources/sprites/world/fireplace.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->Play(true);

    auto smoke_emitter = Component::Create<SmokeEmitter>();

    AddComponent(smoke_emitter);
    AddComponent(animator);

    GetTransform()->Position = {1103, 505};
    GetTransform()->SetSize({125, 175});

    smoke_emitter->Start();
  }
};

}

#endif //SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_
