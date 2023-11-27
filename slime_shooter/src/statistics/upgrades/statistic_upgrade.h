#ifndef SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_STATISTIC_UPGRADE_H_
#define SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_STATISTIC_UPGRADE_H_

#include "string"
#include "../statistic_type.h"

namespace slime_shooter::statistic_upgrades {

enum class UpgradeType {
  Minor, Regular, Major, Base
};

struct StatisticUpgrade {
  std::string name;
  std::string label;
  float value;
  StatisticType statistic_type;
  UpgradeType upgrade_type;
};

const int kMaxStatisticUpgrades = 17;

const StatisticUpgrade DefaultStatisticUpgradeValues[kMaxStatisticUpgrades] = {
    {"DamageMinor", "Damage", 0.85, StatisticType::Damage, UpgradeType::Minor},
    {"DamageRegular", "Damage", 1.15, StatisticType::Damage, UpgradeType::Regular},
    {"DamageMajor", "Damage", 1.5, StatisticType::Damage, UpgradeType::Major},

    {"FireRateMinor", "FireRate", -0.02, StatisticType::FireRate, UpgradeType::Minor},
    {"FireRateRegular", "FireRate", -0.015, StatisticType::FireRate, UpgradeType::Regular},
    {"FireRateMajor", "FireRate", -0.025, StatisticType::FireRate, UpgradeType::Major},

    {"Health", "Health", 1, StatisticType::Health, UpgradeType::Base},

    {"MaxHealthMinor", "Health", 1, StatisticType::MaxHealth, UpgradeType::Minor},
    {"MaxHealthRegular", "Health", 1, StatisticType::MaxHealth, UpgradeType::Regular},
    {"NaxHealthMajor", "Health", 1, StatisticType::MaxHealth, UpgradeType::Major},

    {"ProjectileSizeMinor", "Bullet size", 0.1, StatisticType::ProjectileSize, UpgradeType::Minor},
    {"ProjectileSizeRegular", "Bullet size", 0.15, StatisticType::ProjectileSize, UpgradeType::Regular},
    {"ProjectileSizeMajor", "Bullet size", 0.25, StatisticType::ProjectileSize, UpgradeType::Major},

    {"Speed", "Speed", 0.25, StatisticType::MovementSpeed, UpgradeType::Base},

    {"TurretSpeedMinor", "Turret speed", 0.2, StatisticType::TurretSpeed, UpgradeType::Minor},
    {"TurretSpeedRegular", "Turret speed", 0.35, StatisticType::TurretSpeed, UpgradeType::Regular},
    {"TurretSpeedMajor", "Turret speed", 0.5, StatisticType::TurretSpeed, UpgradeType::Major},
};

std::unordered_map<std::string, StatisticUpgrade> StatisticUpgradeMap;

void InitializeStatisticUpgradeMap() {
  for (const auto& upgrade : DefaultStatisticUpgradeValues) {
    // Assuming the 'name' is unique
    StatisticUpgradeMap[upgrade.name] = upgrade;
  }
}

// Function to get a StatisticUpgrade based on the 'name'
StatisticUpgrade GetStatisticUpgrade(const std::string& name) {
  auto it = StatisticUpgradeMap.find(name);
  return (it != StatisticUpgradeMap.end()) ? it->second : StatisticUpgrade{}; // Return a default-constructed object if not found
}

}

#endif //SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_SLIME_SHOOTER_SRC_STATISTICS_UPGRADES_STATISTIC_UPGRADE_H_
