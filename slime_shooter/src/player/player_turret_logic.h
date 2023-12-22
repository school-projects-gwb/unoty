#ifndef SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_TURRET_SCRIPT_H_
#define SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_TURRET_SCRIPT_H_

#include "entities/game_object.h"
#include "entities/behaviour_script.h"
#include "entities/artificial_intelligence/circle_path_around_object_ai.h"

using namespace engine::entities;

namespace slime_shooter {

class TurretScript : public BehaviourScript {
 public:
  void OnWake() override {
    transform_ = GetGameObject().GetTransform();
    circle_ai_ = GetGameObject().GetComponentByType<CircleAroundObjectAI>();
    player_statistics_ = GameObject::GetSceneObjectByName("Player")->GetComponentByType<Statistics>();

    timer_.Start();
  }

  void OnUpdate() override {
    auto pos = circle_ai_->GetNewPosition();
    *transform_ = *pos;

    ProcessFireBullets();
  }

  void ProcessFireBullets() {
    if (!timer_.HasElapsed(GetFireRate())) return;

    // target closest enemy
    if (enemy_target_ == nullptr || !enemy_target_->GetIsReady()) enemy_target_ = GameObject::Cast<EnemyBase>(GetTarget());
    if (enemy_target_ == nullptr) return;

    timer_.Start();
    enemy_target_->TakeDamage(true);
  }

  double GetFireRate() {
    float fire_rate = player_statistics_->Get(StatisticType::TurretFireRate);
    return fire_rate < min_fire_rate_ ? min_fire_rate_ : fire_rate;
  }

  std::shared_ptr<GameObject> GetTarget() {
    auto enemies = GameObject::GetSceneObjectsByTagName("Enemy");
    std::pair<float, std::shared_ptr<GameObject>> closest {std::numeric_limits<float>::max(), nullptr};

    for(const auto& enemy: enemies){
      if(enemy->GetIsReady() && enemy->GetIsActive()) {
        auto x = enemy->GetTransform()->Position.x - transform_->Position.x;
        auto y = enemy->GetTransform()->Position.y - transform_->Position.y;
        auto distance = std::sqrt((x*x) + (y*y));

        if(distance < closest.first){
          closest = {distance, enemy};
        }
      }
    }

    if(closest.first < player_statistics_->Get(StatisticType::TurretRange)){
      return closest.second;
    }

    return nullptr;
  }

 private:
  const float min_fire_rate_ = 0.075f;
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<Transform> transform_;
  std::shared_ptr<CircleAroundObjectAI> circle_ai_;
  engine::utility::Timer timer_{};
  std::shared_ptr<EnemyBase> enemy_target_;
};

}

#endif //SLIME_SHOOTER_SRC_PLAYER_SLIME_SHOOTER_SRC_TURRET_SCRIPT_H_
