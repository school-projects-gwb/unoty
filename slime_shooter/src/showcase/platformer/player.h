#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_H_
#define SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_H_

#include "entities/game_object.h"
#include "entities/animator.h"
#include "entities/physics/box_collider.h"
#include "entities/physics/rigid_body.h"
#include "player/player_light.h"
#include "player_movement.h"

using namespace engine::entities;

namespace slime_shooter::showcase {

class Player : public GameObject {
 public:
  Player() {
    auto animator = Component::Create<Animator>("resources/sprites/player/player_default_state.png", 4, Point{32, 32});
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_up.png", SpriteAnimationState::North);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_right.png", SpriteAnimationState::East);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_down.png", SpriteAnimationState::South);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_left.png", SpriteAnimationState::West);

    auto script = Component::Create<PlayerMovement>();

    GetTransform()->SetSize({100, 100});

    auto collider = Component::Create<BoxCollider>(Vector2d{100, 100});
    auto rigid_body = Component::Create<RigidBody>(*this, engine::physics::RigidBodyType::Dynamic, collider);

    AddComponent(animator);
    AddComponent(script);
    AddComponent(rigid_body);
    AddComponent(collider);

    auto light = GameObject::Create<PlayerLight>();
    AddChildObject(light);

    SetLayer(5);
  }
};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_H_
