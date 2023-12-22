#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_LIGHT_LOGIC_H_
#define SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_LIGHT_LOGIC_H_

#include "entities/behaviour_script.h"
#include "entities/light_source.h"

using namespace engine::entities;

namespace slime_shooter::showcase {

class PlayerLightLogic : public BehaviourScript {
 private:
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<LightSource> light_source_;

  std::shared_ptr<Transform> player_transform_;

  Vector2d offset_position_ = {415, 425};

  void OnStart() override {
    light_source_ = GetGameObject().GetComponentByType<LightSource>();
    transform_ = GetGameObject().GetTransform();
    player_transform_ = GetGameObject().GetParent()->GetTransform();
  }

  void OnUpdate() override {
    transform_->Position = player_transform_->Position - offset_position_;
  }
};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_LIGHT_LOGIC_H_