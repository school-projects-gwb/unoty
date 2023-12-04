#ifndef SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_STATISTIC_UPGRADE_H_
#define SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_STATISTIC_UPGRADE_H_

#include <utility>

#include "string"
#include "../statistic_type.h"

namespace slime_shooter::statistic_upgrades {

enum class UpgradeType {
  Minor, Regular, Major, Base
};

struct StatisticUpgrade {
  StatisticUpgrade(std::string  name, std::string  label, float value, StatisticType statistic_type,
                   UpgradeType upgrade_type)
      : name(std::move(name)), label(std::move(label)), value(value), statistic_type(statistic_type), upgrade_type(upgrade_type) {}

  StatisticUpgrade() : value(0.0), statistic_type(StatisticType::Damage), upgrade_type(UpgradeType::Minor) {}

  std::string name;
  std::string label;
  float value{};
  StatisticType statistic_type;
  UpgradeType upgrade_type;
};

const int kMaxStatisticUpgrades = 17;

const StatisticUpgrade DefaultStatisticUpgradeValues[kMaxStatisticUpgrades] = {
    StatisticUpgrade{"DamageMinor", "Damage", 0.85, StatisticType::Damage, UpgradeType::Minor},
    StatisticUpgrade{"DamageRegular", "Damage", 1.15, StatisticType::Damage, UpgradeType::Regular},
    StatisticUpgrade{"DamageMajor", "Damage", 1.5, StatisticType::Damage, UpgradeType::Major},

    StatisticUpgrade{"FireRateMinor", "FireRate", -0.02, StatisticType::FireRate, UpgradeType::Minor},
    StatisticUpgrade{"FireRateRegular", "FireRate", -0.015, StatisticType::FireRate, UpgradeType::Regular},
    StatisticUpgrade{"FireRateMajor", "FireRate", -0.025, StatisticType::FireRate, UpgradeType::Major},

    StatisticUpgrade{"Health", "Health", 1, StatisticType::Health, UpgradeType::Base},

    StatisticUpgrade{"MaxHealthMinor", "Health", 1, StatisticType::MaxHealth, UpgradeType::Minor},
    StatisticUpgrade{"MaxHealthRegular", "Health", 1, StatisticType::MaxHealth, UpgradeType::Regular},
    StatisticUpgrade{"NaxHealthMajor", "Health", 1, StatisticType::MaxHealth, UpgradeType::Major},

    StatisticUpgrade{"ProjectileSizeMinor", "Bullet size", 0.1, StatisticType::ProjectileSize, UpgradeType::Minor},
    StatisticUpgrade{"ProjectileSizeRegular", "Bullet size", 0.15, StatisticType::ProjectileSize, UpgradeType::Regular},
    StatisticUpgrade{"ProjectileSizeMajor", "Bullet size", 0.25, StatisticType::ProjectileSize, UpgradeType::Major},

    StatisticUpgrade{"Speed", "Speed", 0.25, StatisticType::MovementSpeed, UpgradeType::Base},

    StatisticUpgrade{"TurretSpeedMinor", "Turret speed", 0.2, StatisticType::TurretSpeed, UpgradeType::Minor},
    StatisticUpgrade{"TurretSpeedRegular", "Turret speed", 0.35, StatisticType::TurretSpeed, UpgradeType::Regular},
    StatisticUpgrade{"TurretSpeedMajor", "Turret speed", 0.5, StatisticType::TurretSpeed, UpgradeType::Major},
};

std::unordered_map<std::string, StatisticUpgrade> StatisticUpgradeMap;

void InitializeStatisticUpgradeMap() {
  for (const auto& upgrade : DefaultStatisticUpgradeValues)
    StatisticUpgradeMap[upgrade.name] = upgrade;
}

StatisticUpgrade GetStatisticUpgradeByName(const std::string& name) {
  auto it = StatisticUpgradeMap.find(name);
  return (it != StatisticUpgradeMap.end()) ? it->second : StatisticUpgrade{};
}

std::vector<StatisticUpgrade> GetStatisticUpgradesByType(UpgradeType type) {
  std::vector<StatisticUpgrade> upgrades;

  for (const auto& upgrade : StatisticUpgradeMap)
    if (upgrade.second.upgrade_type == type)
      upgrades.push_back(upgrade.second);

  return upgrades;
}

}

#endif //SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_STATISTIC_UPGRADE_H_
