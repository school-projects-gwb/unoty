#ifndef ENGINE_INCLUDE_ENTITIES_ENGINE_INCLUDE_ENTITIES_LIGHT_SOURCE_H_
#define ENGINE_INCLUDE_ENTITIES_ENGINE_INCLUDE_ENTITIES_LIGHT_SOURCE_H_

#include "sprite.h"

namespace engine::entities {

/// @brief Behaves like a Sprite internally, but with some extra logic and rendered during lighting rendering step
class LightSource : public Component {
 public:
  explicit LightSource(std::string sprite_path);
  ~LightSource();

  void Render(const std::unique_ptr<ui::SpriteRenderer>&, const std::shared_ptr<entities::Transform>& transform);

  /// @brief Returns sprite, all properties can be changed (i.e. Color) and are reflected during rendering of the LightSource.
  [[nodiscard]] entities::Sprite &GetSprite();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ENGINE_INCLUDE_ENTITIES_LIGHT_SOURCE_H_
