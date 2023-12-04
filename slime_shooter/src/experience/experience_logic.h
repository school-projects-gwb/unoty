#ifndef SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_LOGIC_H_
#define SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_LOGIC_H_

#include "entities/behaviour_script.h"

using namespace engine::entities;

namespace slime_shooter {

class ExperienceObjectPool;

class ExperienceLogic : public BehaviourScript {
 public:
  void OnUpdate() override {
    if (!is_initialised_) Initialise();
    if (transform_->Position.Distance(player_transform_->Position) > minimum_pickup_distance_) return;
    player_experience_->GainExperience(amount_);
    GetGameObject().SetIsActive(false); // not using object pool here to avoid dealing with circular dependencies
  }

  void SetAmount(int amount) {
    amount_ = amount;
  }

 private:
  float minimum_pickup_distance_ = 100;
  bool is_initialised_ = false;
  int amount_;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<GameObject> player_;
  std::shared_ptr<Transform> player_transform_;
  std::shared_ptr<PlayerExperience> player_experience_;

  void Initialise() {
    is_initialised_ = true;

    transform_ = GetGameObject().GetTransform();

    player_ = GameObject::GetSceneObjectByName("Player");
    player_experience_ = player_->GetComponentByType<PlayerExperience>();
    player_transform_ = player_->GetTransform();
  }
};

}

#endif //SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_LOGIC_H_
