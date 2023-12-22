#ifndef ENGINE_INCLUDE_ENTITIES_CAMERA_H_
#define ENGINE_INCLUDE_ENTITIES_CAMERA_H_

#include "entities/game_object.h"
#include "entities/structs/color.h"

namespace engine::entities {

class Camera : public GameObject {
 public:
  Camera();
  virtual ~Camera();
  virtual void UpdatePosition();

  bool IsObjectInViewport(const std::shared_ptr<Transform> &object_transform, float offset, Point camera_position);
  void SetTrackingTransform(std::shared_ptr<Transform> transform_to_track);
  std::shared_ptr<Transform> GetTrackingTransform();

  /// @brief Sets current world position of camera
  virtual void SetPosition(Point position);

  /// @brief Returns current world position of camera
  virtual Point GetPosition(bool with_offset) const;

  virtual bool HasTrackingTransform() const;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_CAMERA_H_
