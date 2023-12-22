
#ifndef SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_PLAYER_H
#define SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_PLAYER_H

#include "entities/game_object.h"
#include "entities/animator.h"
#include "ai_demo_player_movement.h"
#include "ai_demo_marker.h"

using namespace engine::entities;

namespace slime_shooter {

class AiDemoPlayer : public GameObject {
 public:
  AiDemoPlayer() {
    SetName("AiDemoPlayer");

    auto animator = Component::Create<Animator>("resources/sprites/player/player_default_state.png", 4, Point{32, 32});
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_up.png", SpriteAnimationState::North);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_right.png", SpriteAnimationState::East);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_down.png", SpriteAnimationState::South);
    animator->SetSpriteSheetAtIndex("resources/sprites/player/player_animation_left.png", SpriteAnimationState::West);

    GetTransform()->SetSize({30, 30});
    GetTransform()->Position = {150, 350};

    auto collider = Component::Create<BoxCollider>(Vector2d{30, 30});
    auto find_path_ai = Component::Create<FindPathToObjectAI>();
    find_path_ai->AddInvalidTile("wall");
    find_path_ai->AddWeightedTile("ghost_wall", 50);
    auto script = Component::Create<AiDemoPlayerMovement>();

    auto marker = GameObject::Create<AiDemoMarker>();
    *marker->GetTransform() = *GetTransform();
    AddChildObject(marker);

    AddComponent(animator);
    AddComponent(collider);
    AddComponent(find_path_ai);
    AddComponent(script);

    SetLayer(5);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_PLAYER_H
