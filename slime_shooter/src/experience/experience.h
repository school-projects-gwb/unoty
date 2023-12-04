#ifndef SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_H_
#define SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_H_

#include "entities/game_object.h"
#include "experience_logic.h"

using namespace engine::entities;

namespace slime_shooter {

class Experience : public GameObject {
 public:
  Experience() {
    auto animator = Component::Create<Animator>("resources/sprites/world/experience.png",
                                                4, Point{16, 16}, Point{2, 2});
    animator->SetSpriteSheetAtIndex("resources/sprites/world/experience.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->Play(true);

    AddComponent(animator);

    experience_logic_ = Component::Create<ExperienceLogic>();
    AddComponent(experience_logic_);
    GetTransform()->SetSize({32,32});
    SetLayer(4);
  }

  void SetAmount(int amount) {
    experience_logic_->SetAmount(amount);
  }

  static std::shared_ptr<Experience> Create() {
    auto object = GameObject::Create<Experience>();
    object->SetIsActive(false);

    return object;
  }

 private:
  std::shared_ptr<ExperienceLogic> experience_logic_;
};

}

#endif //SLIME_SHOOTER_SRC_EXPERIENCE_SLIME_SHOOTER_SRC_EXPERIENCE_EXPERIENCE_H_
