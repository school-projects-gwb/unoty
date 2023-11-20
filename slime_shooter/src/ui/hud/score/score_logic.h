#ifndef SLIME_SHOOTER_SRC_UI_HUD_SCORE_SLIME_SHOOTER_SRC_UI_HUD_SCORE_SCORE_LOGIC_H_
#define SLIME_SHOOTER_SRC_UI_HUD_SCORE_SLIME_SHOOTER_SRC_UI_HUD_SCORE_SCORE_LOGIC_H_

#include "entities/behaviour_script.h"
#include "statistics/statistics.h"
#include "score_text.h"

using namespace engine::entities;

namespace slime_shooter {

class ScoreLogic : public BehaviourScript {
 public:
  void OnStart() override {
    auto score_text = GameObject::GetSceneObjectByName("score_text", true);
    score_text_ = GameObject::Cast<ScoreText>(score_text);

    auto player = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player->GetComponentByType<Statistics>();
  }

  void OnUpdate() override {
    score_text_->SetContent("SCORE: " + std::to_string(player_statistics_->GetInt(StatisticType::Score)));
  }

 private:
  std::shared_ptr<ScoreText> score_text_;
  std::shared_ptr<Statistics> player_statistics_;
};

}

#endif //SLIME_SHOOTER_SRC_UI_HUD_SCORE_SLIME_SHOOTER_SRC_UI_HUD_SCORE_SCORE_LOGIC_H_
