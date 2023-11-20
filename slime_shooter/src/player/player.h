#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_H_

#include "entities/game_object.h"
#include "string"
#include "entities/animator.h"
#include "player_movement.h"
#include "statistics/statistics.h"
#include "player_weapon.h"
#include "player_turret.h"

using namespace engine::entities;

namespace slime_shooter {

class Player : public GameObject {
 public:
  Player() {
    SetName("Player");

    auto animator = Component::Create<Animator>("resources/sprites/player/player_default_state.png", 4, Point{32, 32});
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_up.png", SpriteAnimationState::North);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_right.png", SpriteAnimationState::East);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_down.png", SpriteAnimationState::South);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_left.png", SpriteAnimationState::West);

    auto walk_sound = Component::Create<AudioSource>("resources/audio/footstep.wav");
    walk_sound->ToggleLooping();
    walk_sound->SetVolume(10);
    walk_sound->SetSpeed(75);
    
    auto script = Component::Create<MovementScript>();
    auto statistics = Component::Create<Statistics>();

    AddComponent(animator);
    AddComponent(script);
    AddComponent(statistics);
    AddComponent(walk_sound);

    auto weapon = GameObject::Create<PlayerWeapon>();
    AddChildObject(weapon);

    auto turret = GameObject::Create<PlayerTurret>();
    turret->GetTransform()->Position = {800, 650}; // TODO update when turret has AI logic
    AddChildObject(turret);

    GetTransform()->Position = {875, 650};
    GetTransform()->SetSize({100, 100});

    SetLayer(1);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_H_
