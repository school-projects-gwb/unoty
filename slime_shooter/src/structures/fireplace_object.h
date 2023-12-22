#ifndef SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_
#define SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "particle/smoke_emitter.h"
#include "fireplace_light.h"

using namespace engine::entities;

namespace slime_shooter {

class FireplaceObject : public GameObject {
 public:
  FireplaceObject() {
    auto animator = Component::Create<Animator>("resources/sprites/world/fireplace.png", 3, Point{27, 37}, Point{3, 1});
    animator->SetSpriteSheetAtIndex("resources/sprites/world/fireplace.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->SetAnimationFrameTimeSeconds(0.25);
    animator->Play(true);
    AddComponent(animator);

    auto light = GameObject::Create<FireplaceLight>();
    AddChildObject(light);

    auto emitter = Component::Create<SmokeEmitter>();
    emitter->Start();
    AddComponent(emitter);

    GetTransform()->SetSize({125, 175});
    GetTransform()->Position = {1103, 505};
    light->GetTransform()->Position = {GetTransform()->Position.x-575, GetTransform()->Position.y-525};
  }
};

}

#endif //SLIME_SHOOTER_SRC_WORLD_SLIME_SHOOTER_SRC_WORLD_FIREPLACE_OBJECT_H_
