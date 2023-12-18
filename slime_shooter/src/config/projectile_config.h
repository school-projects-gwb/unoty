#ifndef SLIME_SHOOTER_SRC_CONFIG_PROJECTILE_CONFIG_H
#define SLIME_SHOOTER_SRC_CONFIG_PROJECTILE_CONFIG_H

namespace slime_shooter {

struct ProjectileConfig {
  // Should two colliding projectiles destroy eachother (true), or ignore eachother (false)?
  inline static const bool projectile_collision = false;
  inline static const int projectile_speed = 3;
  inline static const int enemy_projectile_pool_size = 100;
  inline static const int player_projectile_pool_size = 100;
  inline static const float default_enemy_fire_rate = 3.0f;
  inline static const float min_fire_rate = 0.075f;
  inline static const float max_attack_distance = 500.0f;
};


} // namespace slime_shooter

#endif //SLIME_SHOOTER_SRC_CONFIG_PROJECTILE_CONFIG_H
