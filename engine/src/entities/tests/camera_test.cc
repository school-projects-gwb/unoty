#include <gtest/gtest.h>
#include "../../../include/entities/transform.h"
#include "../../../include/entities/camera.h"
#include "../../../include/entities/game_object.h"

namespace engine::entities::tests {

TEST(CameraTest, TrackingObjectUpdatePositionCorrect) {
  // Arrange
  auto camera = std::make_unique<Camera>();
  auto transform = std::make_shared<Transform>();

  // Act
  camera->SetTrackingTransform(transform);

  // Assert
  const int new_x_pos = 5;
  transform->Position.x = new_x_pos;
  camera->UpdatePosition();

  EXPECT_EQ(camera->GetTransform()->Position.x, new_x_pos);
}

}