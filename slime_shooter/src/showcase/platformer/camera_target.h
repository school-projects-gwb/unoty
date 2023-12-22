#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_CAMERA_TARGET_H_
#define SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_CAMERA_TARGET_H_

#include "entities/game_object.h"
#include "camera_target_logic.h"
using namespace engine::entities;

namespace slime_shooter::showcase {

class CameraTarget : public GameObject {
 public:
  CameraTarget(const std::shared_ptr<Transform>& camera_transform) {
    auto logic = Component::Create<CameraTargetLogic>(camera_transform);
    AddComponent(logic);

    camera_transform->Position = {0, -500};
  }
};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_CAMERA_TARGET_H_
