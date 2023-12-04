#ifndef SLIME_SHOOTER_SRC_STATISTICS_SLIME_SHOOTER_SRC_STATISTICS_STATISTICS_H_
#define SLIME_SHOOTER_SRC_STATISTICS_SLIME_SHOOTER_SRC_STATISTICS_STATISTICS_H_

#include "entities/behaviour_script.h"
#include "statistic.h"
#include "unordered_map"
#include "upgrades/statistic_upgrade.h"

using namespace engine::entities;

namespace slime_shooter {

class Statistics : public BehaviourScript {
 public:
  void OnStart() override {
    Reset();
  }

  [[nodiscard]] float Get(StatisticType type) const {
    try {
      return statistics_.at(type);
    } catch (const std::out_of_range& e) { return 0; }
  }

  /// @float Casts and returns original float value to int
  [[nodiscard]] int GetInt(StatisticType type) const {
    try {
      return (int) statistics_.at(type);
    } catch (const std::out_of_range& e) { return 0; }
  }

  void Append(StatisticType type, float value_to_append) {
    statistics_[type] = statistics_[type] + value_to_append;
  }

  void Set(StatisticType type, float value) {
    statistics_[type] = value;
  }

  /// @brief Sets value of type_to_set to value of type_value_to_use
  void Set(StatisticType type_to_set, StatisticType type_value_to_use) {
    statistics_[type_to_set] = Get(type_value_to_use);
  }

  [[nodiscard]] statistic_upgrades::UpgradeType GetCurrentUpgradeType() const {
    auto player_level = GetInt(StatisticType::Level);

    if (player_level <= 5) return statistic_upgrades::UpgradeType::Minor;
    if (player_level <= 10) return statistic_upgrades::UpgradeType::Regular;
    if (player_level >= 15) return statistic_upgrades::UpgradeType::Major;

    return statistic_upgrades::UpgradeType::Minor;
  }

  void ApplyUpgrade(const statistic_upgrades::StatisticUpgrade& upgrade) {
    Set(upgrade.statistic_type, Get(upgrade.statistic_type) + upgrade.value);
  }
 private:
  std::unordered_map<StatisticType, float> statistics_;

  void Reset() {
    statistics_.clear();

    for (const auto& default_statistic : DefaultStatisticValues) {
      statistics_.emplace(default_statistic.statistic_type, default_statistic.value);
    }
  }
};

}

#endif //SLIME_SHOOTER_SRC_STATISTICS_SLIME_SHOOTER_SRC_STATISTICS_STATISTICS_H_
