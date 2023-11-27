#ifndef SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_H_
#define SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_H_

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "statistics/upgrades/statistic_upgrade.h"
#include "base_upgrade_symbol.h"

using namespace engine::entities;

namespace slime_shooter  {

class BaseUpgrade : public GameObject {
 public:
  BaseUpgrade(const statistic_upgrades::StatisticUpgrade& upgrade, Vector2d position) {
    auto frame_sprite = Component::Create<Sprite>("resources/sprites/world/pointer_rectangle.png");
    AddComponent(frame_sprite);

    auto symbol = GameObject::Create<BaseUpgradeSymbol>(upgrade, position);
    AddChildObject(symbol);

    GetTransform()->Position = position;
    GetTransform()->SetScale(0.65);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_H_
