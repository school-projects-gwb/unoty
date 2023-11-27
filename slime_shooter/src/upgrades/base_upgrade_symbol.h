#ifndef SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_SYMBOL_H_
#define SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_SYMBOL_H_

#include "engine/engine_config.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "statistics/upgrades/statistic_upgrade.h"

using namespace engine::entities;

namespace slime_shooter  {

class BaseUpgradeSymbol : public GameObject {
 public:
  BaseUpgradeSymbol(statistic_upgrades::StatisticUpgrade upgrade, Vector2d position) {
    std::string symbol_sprite_path = upgrade.name == "Speed" ? "resources/sprites/world/speedbuff.png" : "resources/sprites/world/health-regen.png";
    auto symbol_sprite = Component::Create<Sprite>(symbol_sprite_path);
    AddComponent(symbol_sprite);

    GetTransform()->Position = {(float)position.x + 5, (float)position.y + 13};
    GetTransform()->SetScale(0.55);
  }
};

}

#endif //SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_BASE_UPGRADE_SYMBOL_H_
