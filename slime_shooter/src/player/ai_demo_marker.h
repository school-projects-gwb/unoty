
#ifndef SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_MARKER_H
#define SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_MARKER_H

#include "entities/game_object.h"
#include "entities/sprite.h"
using namespace engine::entities;

namespace slime_shooter {

class AiDemoMarker : public GameObject {
 public:
  AiDemoMarker() {
    SetName("AiDemoMarker");

    auto sprite = Component::Create<Sprite>("resources/sprites/player/marker.png");

    AddComponent(sprite);

    SetLayer(4);
    SetIsActive(false);
  }
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_MARKER_H
