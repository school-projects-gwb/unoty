#include <gtest/gtest.h>

#include "entities/structs/vector.h"

TEST(VectorTest, NormalizationValid) {
  // Arrange
  engine::entities::Vector v(3.0, 4.0);

  // Act
  float expectedX = 3.0 / 5.0;
  float expectedY = 4.0 / 5.0;
  v.normalize();

  // Assert
  EXPECT_FLOAT_EQ(v.x, expectedX);
  EXPECT_FLOAT_EQ(v.y, expectedY);
}
