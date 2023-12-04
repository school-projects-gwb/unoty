#include <gtest/gtest.h>

#include "entities/structs/vector_2d.h"

TEST(VectorTest, NormalizationValid) {
  // Arrange
  engine::entities::Vector2d v(3, 4);
  // Act
  float expected_x = 3.0 / 5.0;
  float expected_y = 4.0 / 5.0;
  v.Normalize();

  // Assert
  EXPECT_FLOAT_EQ(v.x, expected_x);
  EXPECT_FLOAT_EQ(v.y, expected_y);
}
