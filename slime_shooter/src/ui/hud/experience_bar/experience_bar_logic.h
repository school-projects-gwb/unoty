#ifndef SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_LOGIC_H_
#define SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_LOGIC_H_

#include "entities/behaviour_script.h"
#include "statistics/statistics.h"
#include "experience_bar_fill.h"
#include "experience_bar_text.h"

using namespace engine::entities;

namespace slime_shooter {

class ExperienceBarLogic : public BehaviourScript {
 public:
  void OnStart() override {
    auto experience_bar_fill = GameObject::GetSceneObjectByName("experience_bar_fill", true);
    experience_bar_fill_transform_ = experience_bar_fill->GetTransform();
    experience_bar_fill_height_ = experience_bar_fill_transform_->GetSize().y;
    experience_bar_fill_max_width_ = experience_bar_fill_transform_->GetSize().x;

    auto experience_bar_text = GameObject::GetSceneObjectByName("experience_bar_text", true);
    experience_bar_text_ = GameObject::Cast<ExperienceBarText>(experience_bar_text);

    auto player = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player->GetComponentByType<Statistics>();
  }

  void OnUpdate() override {
    int current_experience = player_statistics_->GetInt(StatisticType::Experience);
    int max_experience = player_statistics_->GetInt(StatisticType::MaxExperience);

    float experience_percentage = static_cast<float>(current_experience) / static_cast<float>(max_experience);
    int fill_width = static_cast<int>(experience_percentage * experience_bar_fill_max_width_);

    experience_bar_fill_transform_->SetSize({fill_width, experience_bar_fill_height_});
    experience_bar_text_->SetContent("LVL." + std::to_string(player_statistics_->GetInt(StatisticType::Level)));
  }

 private:
  std::shared_ptr<Transform> experience_bar_fill_transform_;
  std::shared_ptr<ExperienceBarText> experience_bar_text_;
  int experience_bar_fill_max_width_;
  int experience_bar_fill_height_;
  std::shared_ptr<Statistics> player_statistics_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_SLIME_SHOOTER_SRC_UI_EXPERIENCE_BAR_EXPERIENCE_BAR_LOGIC_H_
