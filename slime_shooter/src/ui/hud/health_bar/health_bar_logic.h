#ifndef SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_LOGIC_H_
#define SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_LOGIC_H_

#include "entities/behaviour_script.h"
#include "statistics/statistics.h"
#include "health_bar_fill.h"
#include "health_bar_text.h"

using namespace engine::entities;

namespace slime_shooter {

class HealthBarLogic : public BehaviourScript {
 public:
  void OnStart() override {
    auto health_bar_fill = GameObject::GetSceneObjectByName("health_bar_fill", true);
    health_bar_fill_transform_ = health_bar_fill->GetTransform();
    health_bar_fill_height_ = health_bar_fill_transform_->GetSize().y;
    health_bar_fill_max_width_ = health_bar_fill_transform_->GetSize().x;

    auto health_bar_text = GameObject::GetSceneObjectByName("health_bar_text", true);
    score_text_ = GameObject::Cast<HealthBarText>(health_bar_text);

    auto player = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player->GetComponentByType<Statistics>();
  }

  void OnUpdate() override {
    int current_health = player_statistics_->GetInt(StatisticType::Health);
    int max_health = player_statistics_->GetInt(StatisticType::MaxHealth);

    float health_percentage = static_cast<float>(current_health) / static_cast<float>(max_health);
    int fill_width = static_cast<int>(health_percentage * health_bar_fill_max_width_);

    health_bar_fill_transform_->SetSize({fill_width, health_bar_fill_height_});
    score_text_->SetContent(std::to_string(current_health) + "/" + std::to_string(max_health));
  }

 private:
  std::shared_ptr<Transform> health_bar_fill_transform_;
  std::shared_ptr<HealthBarText> score_text_;
  int health_bar_fill_max_width_;
  int health_bar_fill_height_;
  std::shared_ptr<Statistics> player_statistics_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_HEALTH_BAR_SLIME_SHOOTER_SRC_UI_HEALTH_BAR_HEALTH_BAR_LOGIC_H_
