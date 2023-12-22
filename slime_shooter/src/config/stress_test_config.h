#ifndef SLIME_SHOOTER_SRC_CONFIG_STRESS_TEST_CONFIG_H
#define SLIME_SHOOTER_SRC_CONFIG_STRESS_TEST_CONFIG_H

namespace slime_shooter {

struct StressTestConfig {
  inline static bool stress_test_enabled = false;
  inline static const int hotkey_increase_enemy_pool_amount = 25;
  inline static int alive_enemies = 0;
  inline static int enemy_pool_size = 0;
  inline static bool viewport_rendering_enabled = true;
};

} // namespace slime_shooter

#endif //SLIME_SHOOTER_SRC_CONFIG_STRESS_TEST_CONFIG_H
