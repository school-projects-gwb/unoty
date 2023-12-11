#ifndef ENGINE_INCLUDE_ENTITIES_FORESIGHT_CAMERA_H
#define ENGINE_INCLUDE_ENTITIES_FORESIGHT_CAMERA_H

#include "camera.h"
namespace engine::entities {

class ForesightCamera : public Camera {
 public:
  ForesightCamera(float offset_max_size, float offset_velocity);
  ~ForesightCamera();

  /// @brief Updates the position of the foresight camera.
  void UpdatePosition() override;

  /// @brief Sets current world position of camera excluding offsets
  void SetPosition(Point position) override;

  Point GetPosition(bool with_offset) const override;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_FORESIGHT_CAMERA_H
