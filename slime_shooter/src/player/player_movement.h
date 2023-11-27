#ifndef DEBUG_APP__MOVEMENT_SCRIPT_H_
#define DEBUG_APP__MOVEMENT_SCRIPT_H_

#include <unordered_map>
#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/animator.h"
#include "entities/structs/input.h"
#include "entities/structs/vector_2d.h"
#include "statistics/statistics.h"

using namespace engine::entities;

namespace slime_shooter {

class MovementScript : public BehaviourScript {
 public:
  void OnStart() override {
    transform_ = GetGameObject().GetTransform();
    animator_ = GetGameObject().GetComponentByType<Animator>();
    walk_sound_ = GetGameObject().GetComponentByType<AudioSource>();
    statistics_ = GetGameObject().GetComponentByType<Statistics>();
  }

  void OnInput() override {
    Vector2d vector {0, 0};

    for (auto key : Input::GetActiveKeys()) {
      if (key == Key::UnoUpArrow) vector.y--;
      if (key == Key::UnoDownArrow) vector.y++;
      if (key == Key::UnoLeftArrow) vector.x--;
      if (key == Key::UnoRightArrow) vector.x++;
    }

    auto animation_state = DetermineAnimationState(vector.x, vector.y);
    ProcessAnimation(animation_state);

    vector.normalize();
    // Update character position with normalized movement
    float movement_speed = statistics_->Get(StatisticType::MovementSpeed);

    transform_->Position.x += vector.x * movement_speed;
    transform_->Position.y += vector.y * movement_speed;
  }

  SpriteAnimationState DetermineAnimationState(int x_axis, int y_axis) {
    if (x_axis == 0 && y_axis == 0) {
      if (is_moving_) animator_->Stop();
      current_animation_state_ = SpriteAnimationState::Reset;
      is_moving_ = false;
      return SpriteAnimationState::Default;
    } else if (y_axis < 0) {
      return SpriteAnimationState::North;
    } else if (y_axis > 0) {
      return SpriteAnimationState::South;
    } else if (x_axis < 0) {
      return SpriteAnimationState::West;
    } else if (x_axis > 0) {
      return SpriteAnimationState::East;
    }
  }


 private:
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Animator> animator_;
  std::shared_ptr<AudioSource> walk_sound_;
  std::shared_ptr<Statistics> statistics_;

  bool is_moving_ = false;
  SpriteAnimationState previous_animation_state_;
  SpriteAnimationState current_animation_state_;

  void ProcessAnimation(SpriteAnimationState animation_state) {
    if (animation_state == SpriteAnimationState::Default) {
      walk_sound_->Stop();
      return;
    }

    previous_animation_state_ = current_animation_state_;
    current_animation_state_ = animation_state;
    if (current_animation_state_ == previous_animation_state_) return;

    is_moving_ = true;
    animator_->SetCurrentAnimationSpriteSheet(animation_state);
    animator_->Play(true);
    walk_sound_->Play();
  }
};

}

#endif //DEBUG_APP__MOVEMENT_SCRIPT_H_
