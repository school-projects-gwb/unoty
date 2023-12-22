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

class PlayerMovement : public BehaviourScript {
 public:
  void StopWalkSound() {
    walk_sound_->Stop();
  }

 private:
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Animator> animator_;
  std::shared_ptr<RigidBody> rigid_body_;
  std::shared_ptr<AudioSource> walk_sound_;
  std::shared_ptr<Statistics> statistics_;

  bool is_moving_ = false;
  SpriteAnimationState previous_animation_state_;
  SpriteAnimationState current_animation_state_;

  void OnStart() override {
    transform_ = GetGameObject().GetTransform();
    animator_ = GetGameObject().GetComponentByType<Animator>();
    statistics_ = GetGameObject().GetComponentByType<Statistics>();
    rigid_body_ = GetGameObject().GetComponentByType<RigidBody>();

    walk_sound_ = Component::Create<AudioSource>("resources/audio/footstep.wav");
    walk_sound_->ToggleLooping();
    walk_sound_->SetVolume(10);
    GetGameObject().AddComponent(walk_sound_);
  }

  void OnInput() override {
    Vector2d vector{0, 0};

    for (auto key : Input::GetActiveKeys()) {
      switch (key) {
        case Key::UnoW:
          vector.y--;
        break;
        case Key::UnoS:
          vector.y++;
        break;
        case Key::UnoA:
          vector.x--;
        break;
        case Key::UnoD:
          vector.x++;
        break;
        default:break;
      }
    }

    if (Input::IsGamepadPluggedIn() && vector.x == 0 && vector.y == 0) {
      for (auto btn : Input::GetActiveGamepadButtons()) {
        if (btn == GamepadButton::Up) vector.y--;
        if (btn == GamepadButton::Down) vector.y++;
        if (btn == GamepadButton::Left) vector.x--;
        if (btn == GamepadButton::Right) vector.x++;
      }
    }

    auto animation_state = DetermineAnimationState(static_cast<int>(vector.x), static_cast<int>(vector.y));
    ProcessAnimation(animation_state);

    if (vector.x == 0 && vector.y == 0) {
      rigid_body_->SetLinearVelocity(vector);
      return;
    }

    vector.Normalize();
    // Update character position with normalized movement
    float movement_speed = statistics_->Get(StatisticType::MovementSpeed);

    vector.x *= movement_speed;
    vector.y *= movement_speed;
    rigid_body_->SetLinearVelocity(vector);
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
    } else {
      return SpriteAnimationState::East;
    }
  }

  void ProcessAnimation(SpriteAnimationState animation_state) {
    if (animation_state == SpriteAnimationState::Default) {
      walk_sound_->Stop();
      return;
    }
   
    if(previous_animation_state_ == animation_state) return;
    previous_animation_state_ = current_animation_state_;
    current_animation_state_ = animation_state;

    is_moving_ = true;
    animator_->SetCurrentAnimationSpriteSheet(animation_state);
    animator_->Play(true);
    walk_sound_->Play();
  }
};

}

#endif //DEBUG_APP__MOVEMENT_SCRIPT_H_
