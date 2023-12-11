#ifndef SLIME_SHOOTER_SRC_STATISTICS_SLIME_SHOOTER_SRC_STATISTICS_STATISTIC_OBJECT_H_
#define SLIME_SHOOTER_SRC_STATISTICS_SLIME_SHOOTER_SRC_STATISTICS_STATISTIC_OBJECT_H_

#include "statistic_type.h"

namespace slime_shooter {

struct Statistic {
  StatisticType statistic_type;
  float value;
};

const int kMaxStatistics = 11;

const Statistic DefaultStatisticValues[kMaxStatistics] = {
    {StatisticType::Damage, 1},
    {StatisticType::Experience, 0},
    {StatisticType::FireRate, 0.3},
    {StatisticType::Health, 5},
    {StatisticType::Level, 1},
    {StatisticType::MaxExperience, 12},
    {StatisticType::MaxHealth, 5},
    {StatisticType::ProjectileSize, 1},
    {StatisticType::Score, 0},
    {StatisticType::MovementSpeed, 3},
    {StatisticType::TurretSpeed, 3}
};

}

#endif //SLIME_SHOOTER_SRC_STATISTICS_SLIME_SHOOTER_SRC_STATISTICS_STATISTIC_OBJECT_H_
