#ifndef SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_SPAWNER_H_
#define SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_SPAWNER_H_

#include "entities/behaviour_script.h"
#include "enemy_spawner_logic.h"
#include "entities/component.h"

using namespace engine::entities;

namespace slime_shooter {

class EnemySpawner : public GameObject {
 public:
  EnemySpawner() {
    auto spawner_logic = Component::Create<EnemySpawnerLogic>();
    AddComponent(spawner_logic);
  }
};

}

#endif //SLIME_SHOOTER_SRC_ENEMIES_SLIME_SHOOTER_SRC_ENEMIES_ENEMY_SPAWNER_H_
