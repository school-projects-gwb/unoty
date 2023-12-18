#ifndef ENGINE_INCLUDE_ENTITIES_SCENE_ENGINE_INCLUDE_ENTITIES_SCENE_SCENE_LIGHTING_H_
#define ENGINE_INCLUDE_ENTITIES_SCENE_ENGINE_INCLUDE_ENTITIES_SCENE_SCENE_LIGHTING_H_

#include "memory"
#include "rendering/sprite_renderer.h"

namespace engine::entities {

/// @brief Contains Scene ambient lighting color information
///
/// When not manually setting the lighting for a Scene it defaults to having no lighting effects
class SceneLighting {
 public:
  explicit SceneLighting(entities::Color lighting_color = {255, 255, 255, 255});
  ~SceneLighting();

  /// @brief Starts lighting step, used internally
  void StartRenderLighting(const std::unique_ptr<engine::ui::SpriteRenderer>& sprite_renderer) const;

  /// @brief Can be called dynamically during runtime to change the lighting color
  void SetLightingColor(entities::Color lighting_color);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_SCENE_ENGINE_INCLUDE_ENTITIES_SCENE_SCENE_LIGHTING_H_
