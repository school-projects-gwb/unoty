
#ifndef SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_PLAYER_MOVEMENT_H
#define SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_PLAYER_MOVEMENT_H

#include "entities/behaviour_script.h"
#include "entities/animator.h"
#include "entities/audio_source.h"
#include "entities/artificial_intelligence/find_path_to_object_ai.h"
#include "entities/structs/input.h"
using namespace engine::entities;

namespace slime_shooter {

class AiDemoPlayerMovement : public BehaviourScript {
 public:
  void StopWalkSound() {
    walk_sound_->Stop();
  }
 private:
  std::shared_ptr<Transform> target_;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Transform> bounds_;
  std::shared_ptr<GameObject> marker_;
  std::shared_ptr<Animator> animator_;
  std::shared_ptr<AudioSource> walk_sound_;
  std::shared_ptr<AudioSource> buzzer_sound_;
  std::shared_ptr<FindPathToObjectAI> find_path_ai_;

  bool is_moving_ = false;
  SpriteAnimationState previous_animation_state_;
  SpriteAnimationState current_animation_state_;

  void OnStart() override {
    target_ = std::make_shared<Transform>();
    marker_ = GetGameObject().GetChildObjects()[0];
    transform_ = GetGameObject().GetTransform();
    animator_ = GetGameObject().GetComponentByType<Animator>();
    target_->SetSize(transform_->GetSize());

    marker_->GetTransform()->SetSize(transform_->GetSize());

    find_path_ai_ = GetGameObject().GetComponentByType<FindPathToObjectAI>();
    find_path_ai_->Init(target_);

    bounds_ = std::make_shared<Transform>();
    bounds_->Position = {100, 100};
    bounds_->SetSize({900, 600});

    walk_sound_ = Component::Create<AudioSource>("resources/audio/footstep.wav");
    walk_sound_->ToggleLooping();
    walk_sound_->SetVolume(10);

    GetGameObject().AddComponent(walk_sound_);

    buzzer_sound_ = Component::Create<AudioSource>("resources/audio/wrong_buzzer.wav");
    buzzer_sound_->SetVolume(10);

    GetGameObject().AddComponent(buzzer_sound_);
  }

  void OnUpdate() override {
    if (!find_path_ai_->GetTargetReached()) {
      auto pos = find_path_ai_->GetNewPosition();

      auto animation_state = DetermineAnimationState((int) pos->Position.x, (int) pos->Position.y);
      ProcessAnimation(animation_state);

      *transform_ = *pos;
    } else {
      StopWalkSound();
      if (marker_->GetIsReady()) {
        marker_->SetIsActive(false);
      }

      auto animation_state = DetermineAnimationState(0, 0);
      ProcessAnimation(animation_state);
    }

    if (Input::IsMouseClicked()) {
      auto pos = Input::GetMousePointerPosition();
      auto size = transform_->GetSize();

      Vector2d newPos =  {(pos.x - size.x), (pos.y - size.y)};
      if(!bounds_->IsInPositionBounds(newPos)){
        buzzer_sound_->Play();
        return;
      }

      target_->Position = {newPos};

      if (find_path_ai_->FindPath()) {

        if (!marker_->GetIsReady()) {
          marker_->SetIsActive(true);
        }

        marker_->GetTransform()->Position = target_->Position;
        walk_sound_->Play();
      }
      else {
        buzzer_sound_->Play();
      }
    }
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

#endif //SLIME_SHOOTER_SRC_PLAYER_AI_DEMO_PLAYER_MOVEMENT_H
