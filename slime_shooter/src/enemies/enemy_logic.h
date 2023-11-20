#ifndef SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_LOGIC_H_
#define SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_LOGIC_H_

#include "entities/behaviour_script.h"
#include "entities/game_object.h"
#include "entities/structs/input.h"
#include "statistics/statistics.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemyLogic : public BehaviourScript {
 public:
  void OnStart() override {}
  void OnUpdate() override {}
 private:
  std::shared_ptr<Statistics> player_statistics_;
  std::shared_ptr<Transform> player_transform_;
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_LOGIC_H_
