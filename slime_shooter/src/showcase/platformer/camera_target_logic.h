#ifndef SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_CAMERA_TARGET_LOGIC_H_
#define SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_CAMERA_TARGET_LOGIC_H_

#include "entities/game_object.h"
#include "entities/behaviour_script.h"
#include "utility/timer.h"
#include "entities/structs/input.h"
#include "entities/scene/scene_lighting.h"

using namespace engine::entities;

namespace slime_shooter::showcase {

class CameraTargetLogic : public BehaviourScript {
 public:
  CameraTargetLogic(std::shared_ptr<Transform> camera_transform) {
    camera_transform_ = camera_transform;
  }
 private:
  engine::utility::Timer position_update_timer_;
  double position_update_interval_ = 0.02;

  std::shared_ptr<Transform> camera_transform_;
  bool is_in_final_position = false;

  void OnStart() override {
    position_update_timer_.Start();
  }

  void OnInput() override {
    if (!is_in_final_position) return;

    if (Input::HasActiveKey(Key::UnoUpArrow)) {
      camera_transform_->Position.y = (camera_transform_->Position.y - 12 < -500) ? -500 : (camera_transform_->Position.y - 12);
      UpdateColor();
    }

    if (Input::HasActiveKey(Key::UnoDownArrow)) {
      camera_transform_->Position.y = (camera_transform_->Position.y + 12 > 0) ? 0 : (camera_transform_->Position.y + 12);
      UpdateColor();
    }
  }

  void OnUpdate() override {
    if (is_in_final_position) return;
    if (!position_update_timer_.HasElapsed(position_update_interval_)) return;

    camera_transform_->Position.y += 12;
    camera_transform_->Position.x = 0;
    UpdateColor();

    if (camera_transform_->Position.y >= 0) {
      camera_transform_->Position.y = 0;
      is_in_final_position = true;
      return;
    }

    position_update_timer_.Start();
  }

  void UpdateColor() {
    auto color = CalculateColor(camera_transform_->Position.y);
    engine::Engine::GetInstance().GetActiveScene()->GetLighting()->SetLightingColor(color);
  }

  Color CalculateColor(int y) {
    const int min_y = -500;
    const int max_y = 0;

    y = std::min(std::max(y, min_y), max_y);

    double t = static_cast<double>(y-min_y) / (max_y-min_y);

    Color colorAtMinY = {128, 0, 128, 115}; // purple
    Color colorAtMaxY = {0, 0, 0, 115}; // black

    unsigned char r = static_cast<int>((1 - t) * colorAtMinY.r + t * colorAtMaxY.r);
    unsigned char g = static_cast<int>((1 - t) * colorAtMinY.g + t * colorAtMaxY.g);
    unsigned char b = static_cast<int>((1 - t) * colorAtMinY.b + t * colorAtMaxY.b);
    unsigned char a = static_cast<int>((1 - t) * colorAtMinY.a + t * colorAtMaxY.a);

    if (y == 0) {
      r = 0;
      g = 0;
      b = 0;
    }

    return {r, g, b, a};
  }

};

}

#endif //SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_SLIME_SHOOTER_SRC_SHOWCASE_PLATFORMER_CAMERA_TARGET_LOGIC_H_
