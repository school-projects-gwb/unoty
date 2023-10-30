#ifndef ENGINE_INCLUDE_ENTITIES_SPRITE_H_
#define ENGINE_INCLUDE_ENTITIES_SPRITE_H_

#include "component.h"
#include "engine/renderer.h"

namespace engine::entities {

/// @brief Contains logic for rendering sprite
class Sprite : public Component {
 public:
  Sprite(std::string sprite_path);
  ~Sprite();
  void Render(const std::unique_ptr<engine::ui::Renderer>& renderer, Point& position);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_SPRITE_H_
