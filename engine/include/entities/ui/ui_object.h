#ifndef ENGINE_INCLUDE_ENTITIES_UI_OBJECT_H_
#define ENGINE_INCLUDE_ENTITIES_UI_OBJECT_H_

#include "entities/game_object.h"
#include "rendering/renderer.h"

namespace engine::entities {

/// @brief Base ui object containing size information
class UiObject : public GameObject {
 public:
  UiObject();
  ~UiObject();

  virtual void Render(const std::unique_ptr<ui::Renderer>& renderer);

  /// @brief Used for i.e. simple rectangle; provided it with a background color
  virtual void SetBackgroundColor(entities::Color background_color);
  entities::Color GetBackgroundColor() const;

  /// @brief Use when rendering sprite instead of simple rectangle shape; gets prioritised over SetBackgroundColor
  void SetSpritePath(const std::string& sprite_path);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_UI_OBJECT_H_
