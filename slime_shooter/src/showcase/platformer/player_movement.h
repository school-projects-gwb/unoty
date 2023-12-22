#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_MOVEMENT_H_
#define SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_MOVEMENT_H_

#include "entities/behaviour_script.h"

using namespace engine::entities;

namespace slime_shooter::showcase {

class PlayerMovement : public BehaviourScript {
 private:
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<Animator> animator_;
  std::shared_ptr<RigidBody> rigid_body_;

  engine::utility::Timer jump_timer_;

  float jump_force_ = 1250.0f;
  double jump_duration_ = 0.45;
  double minimum_jump_duration_ = 0.05;

  bool is_jumping_ = false;
  bool is_touching_floor_ = false;
  bool is_space_bar_pressed_ = false;
  int jump_counter_ = 0;

  bool is_moving_ = false;
  SpriteAnimationState previous_animation_state_;
  SpriteAnimationState current_animation_state_;

  Vector2d last_position_ = {10000,10000};

  bool is_slowing_down_ = false;

  void OnStart() override {
    transform_ = GetGameObject().GetTransform();
    animator_ = GetGameObject().GetComponentByType<Animator>();
    rigid_body_ = GetGameObject().GetComponentByType<RigidBody>();
  }

  void OnUpdate() override {
    for (auto key : Input::GetReleasedKeys())
      if (key == Key::UnoSpace)
        if (is_jumping_ && jump_timer_.HasElapsed(minimum_jump_duration_)) is_jumping_ = false;

    if (is_jumping_ && jump_timer_.HasElapsed(minimum_jump_duration_) && !Input::HasActiveKey(Key::UnoSpace)) {
      is_jumping_ = false;
    }

    if (!Input::HasActiveKey(Key::UnoSpace) && is_touching_floor_) is_space_bar_pressed_ = false;

    auto current_position = GetGameObject().GetTransform()->Position;
    auto current_velocity = last_position_ - current_position;

    if (is_jumping_ || !is_touching_floor_) {
      if (current_velocity.y > 0 && current_velocity.y < 8 && jump_timer_.HasElapsed(minimum_jump_duration_)) {
        is_slowing_down_ = true;
        float slowing_force = 500.0f;
        Vector2d slowing_force_vector = {0.0f, slowing_force};

        rigid_body_->ApplyForceTowardsDirection(slowing_force_vector);
      }

      float terminal_velocity = -11.0f;

      if (current_velocity.y < terminal_velocity) {
        float additional_downward_force = 100.0f;
        Vector2d downward_force_vector = {0.0f, additional_downward_force};
        rigid_body_->ApplyForceTowardsDirection(downward_force_vector);
      }
    }

    last_position_ = current_position;

    if (last_position_.y == current_position.y && !is_jumping_)
      is_touching_floor_ = true;

    if (current_position.x >= 1280) engine::Engine::GetInstance().SetActiveScene("menu_scene");
  }

  void OnInput() override {
    Vector2d vector {0, 0};

    for (auto key : Input::GetActiveKeys()) {
      if (key == Key::UnoLeftArrow) vector.x--;
      if (key == Key::UnoRightArrow) vector.x++;

      if (key == Key::UnoSpace && !is_jumping_ && is_touching_floor_ && !is_space_bar_pressed_) {
        is_space_bar_pressed_ = true;
        StartJump();
      }
    }



    auto animation_state = DetermineAnimationState(vector.x, vector.y);
    ProcessAnimation(animation_state);

    if (vector.x == 0 && vector.y == 0)
    {
      rigid_body_->SetLinearVelocity(vector);

      if (is_jumping_)
        ContinueJump();

      return;
    }

    vector.Normalize();
    // Update character position with normalized movement
    float movement_speed = is_slowing_down_ ? 7 : 6;

    vector.x *= movement_speed;
    vector.y *= movement_speed;
    rigid_body_->SetLinearVelocity(vector);

    if (is_jumping_) {
      ContinueJump();
    }
  }

  void StartJump() {
    if (jump_counter_ == 1) return;

    is_jumping_ = true;
    jump_timer_.Start();

    jump_counter_++;
  }

  void ContinueJump() {
    double elapsed_time = jump_timer_.GetElapsedSeconds();
    double remaining_time = jump_duration_ - elapsed_time;

    if (remaining_time <= 0.0) {
      is_jumping_ = false;
    } else {
      float force_factor = static_cast<float>(remaining_time / jump_duration_);
      float current_jump_force = jump_force_ * force_factor;

      if (!is_slowing_down_)
        rigid_body_->ApplyForceTowardsDirection(Vector2d(0.0f, -current_jump_force));
    }
  }

  void OnCollisionEnter(engine::entities::GameObject *&colliding_object) override {
    is_touching_floor_ = true;
    is_slowing_down_ = false;
    is_jumping_ = false;
    jump_counter_ = 0;
  }

  void OnCollisionExit(engine::entities::GameObject *&colliding_object) override {
    is_touching_floor_ = false;
  }

  SpriteAnimationState DetermineAnimationState(int x_axis, int y_axis) {
    if (x_axis == 0 && y_axis == 0) {
      if (is_moving_) animator_->Stop();
      current_animation_state_ = SpriteAnimationState::Reset;
      is_moving_ = false;
      return SpriteAnimationState::Default;
    } else if (x_axis < 0) {
      return SpriteAnimationState::West;
    } else {
      return SpriteAnimationState::East;
    }
  }

  void ProcessAnimation(SpriteAnimationState animation_state) {
    if (animation_state == SpriteAnimationState::Default) {
      return;
    }

    previous_animation_state_ = current_animation_state_;
    current_animation_state_ = animation_state;
    if (current_animation_state_ == previous_animation_state_) return;

    is_moving_ = true;
    animator_->SetCurrentAnimationSpriteSheet(animation_state);
    animator_->Play(true);
  }
};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_PLAYER_MOVEMENT_H_
