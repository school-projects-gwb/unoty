#ifndef ENGINE_INCLUDE_ENTITIES_CAMERA_H_
#define ENGINE_INCLUDE_ENTITIES_CAMERA_H_

#include "entities/game_object.h"
#include "entities/structs/color.h"

namespace engine::entities {

class Camera : public GameObject {
 public:
  Camera();
  ~Camera();
  void UpdatePosition();
  void SetBackgroundColor(Color color);
  void SetSize(Point size);
  void SetTrackingTransform(std::shared_ptr<Transform> transform_to_track);
  std::shared_ptr<Transform> GetTrackingTransform();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_CAMERA_H_
