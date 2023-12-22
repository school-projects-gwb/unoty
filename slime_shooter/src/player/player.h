#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_H_

#include "entities/game_object.h"
#include "string"
#include "entities/animator.h"
#include "player_movement.h"
#include "statistics/statistics.h"
#include "player_weapon.h"
#include "player_turret.h"
#include "player_experience.h"
#include "player_health.h"
#include "entities/physics/box_collider.h"
#include "player_light.h"
#include "player_leveling_effect.h"

using namespace engine::entities;

namespace slime_shooter {

class Player : public GameObject {
 public:
  Player(engine::physics::RigidBodyType body_type = engine::physics::RigidBodyType::Dynamic) {
    auto player_size = Point{100, 100};

    SetName("Player");
    SetTagName("Player");

    auto animator = Component::Create<Animator>("resources/sprites/player/player_default_state.png", 4, Point{32, 32});
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_up.png", SpriteAnimationState::North);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_right.png", SpriteAnimationState::East);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_down.png", SpriteAnimationState::South);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_left.png", SpriteAnimationState::West);

    auto script = Component::Create<PlayerMovement>();
    auto statistics = Component::Create<Statistics>();
    auto leveling_effect = GameObject::Create<PlayerLevelingEffect>(10, Vector2d{50,50}, player_size);
    auto experience = Component::Create<PlayerExperience>();

    experience->SetLevelUpCallback([leveling_effect]() {
      leveling_effect->Start();
    });

    GetTransform()->SetSize(player_size);

    auto collider = Component::Create<BoxCollider>(Vector2d{100, 100});
    auto rigid_body = Component::Create<RigidBody>(*this, body_type, collider);

    auto health = GameObject::Create<PlayerHealth>();

    AddComponent(animator);
    AddComponent(script);
    AddComponent(statistics);
    AddComponent(experience);
    AddComponent(rigid_body);
    AddComponent(collider);
    AddComponent(health);
    AddComponent(leveling_effect);

    auto weapon = GameObject::Create<PlayerWeapon>();
    AddChildObject(weapon);

    auto light = GameObject::Create<PlayerLight>();
    AddChildObject(light);

    auto turret = GameObject::Create<PlayerTurret>();
    AddChildObject(turret);
    turret->Init();

    rigid_body->SetPosition({875, 650});

    SetLayer(5);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_PLAYER_PLAYER_H_
