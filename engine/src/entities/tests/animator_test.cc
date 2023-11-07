#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entities/animator.h"

using ::testing::HasSubstr;

namespace engine::entities::tests {

TEST(CameraTest, SpritesInSheetInvalidIntegerSqrtError) {
  // Arrange
  testing::internal::CaptureStderr();

  // Act
  Animator animator("", 3, {32, 32});
  std::string console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_THAT(console_output, HasSubstr("sprites_in_sheet does not translate to an equal amount of rows and columns"));
}

TEST(CameraTest, SpritesInSheetValidIntegerSqrtNoError) {
  // Arrange
  testing::internal::CaptureStderr();

  // Act
  Animator animator("", 4, {32, 32});
  std::string console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_EQ(console_output, "");
}

TEST(CameraTest, SetCurrentAnimationSpriteSheetInvalidIndexError) {
  // Arrange
  testing::internal::CaptureStderr();

  // Act
  Animator animator("", 3, {32, 32});
  animator.SetCurrentAnimationSpriteSheet(1000); // Index does not exist
  std::string console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_THAT(console_output, HasSubstr("Animator: No valid sprite sheet at index"));
}

TEST(CameraTest, SetCurrentAnimationSpriteSheetValidIndexNoError) {
  // Arrange
  testing::internal::CaptureStderr();

  // Act
  Animator animator("", 4, {32, 32});
  int insert_index = 1;
  animator.SetSpriteSheetAtIndex("", insert_index);
  animator.SetCurrentAnimationSpriteSheet(insert_index); // Index does not exist
  std::string console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_EQ(console_output, "");
}

}