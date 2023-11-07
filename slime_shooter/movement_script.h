#ifndef DEBUG_APP__MOVEMENT_SCRIPT_H_
#define DEBUG_APP__MOVEMENT_SCRIPT_H_

#include <iostream>
#include <unordered_map>
#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/animator.h"

using namespace engine::entities;

class MovementScript : public BehaviourScript {
 public:
  void OnStart() override {
    game_object_ = GetGameObject();
    transform_ = game_object_->GetTransform();
    animator_ = game_object_->GetComponentByType<Animator>();
  }

  void OnUpdate() override {
    // No need to go through the logic if object isn't moving to begin with
    if (!is_moving_) return;

    if (last_pos_x_ == transform_->Position.x && last_pos_y_ == transform_->Position.y) {
      animator_->Stop();
      is_moving_ = false;
    }

    last_pos_x_ = transform_->Position.x;
    last_pos_y_ = transform_->Position.y;
  }

  void OnInput(const Key& key) override {
    // TODO movement should use PLayer Speed, implement later @jvanhouts
    switch (key) {
      case Key::Up:
        transform_->Position.y -= 10;
        ProcessAnimation(SpriteAnimationState::North);
        break;
      case Key::Down:
        transform_->Position.y += 10;
        ProcessAnimation(SpriteAnimationState::South);
        break;
      case Key::Left:
        transform_->Position.x -= 10;
        ProcessAnimation(SpriteAnimationState::West);
        break;
      case Key::Right:
        transform_->Position.x += 10;
        ProcessAnimation(SpriteAnimationState::East);
        break;
      default:
        break;
    }
  }

 private:
  int last_pos_x_, last_pos_y_;

  std::shared_ptr<GameObject> game_object_;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Animator> animator_;

  bool is_moving_ = false;
  SpriteAnimationState previous_animation_state_;
  SpriteAnimationState current_animation_state_;

  void ProcessAnimation(SpriteAnimationState animation_state) {
    if (is_moving_ && (current_animation_state_ == animation_state || previous_animation_state_ == animation_state)) return;

    animator_->SetCurrentAnimationSpriteSheet(animation_state);
    animator_->Play(true);
    previous_animation_state_ = current_animation_state_;
    current_animation_state_ = animation_state;
    is_moving_ = true;
  }
};

#endif //DEBUG_APP__MOVEMENT_SCRIPT_H_
