#ifndef ENGINE_INCLUDE_ENTITIES_CAMERA_H_
#define ENGINE_INCLUDE_ENTITIES_CAMERA_H_

#include "entities/game_object.h"
#include "entities/structs/color.h"

namespace engine::entities {

/// @brief Contains logic to follow certain objects
class Camera : public GameObject {
 public:
  Camera();
  ~Camera();
  void SetBackgroundColor(Color color);
  void SetSize(Point size);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_CAMERA_H_
