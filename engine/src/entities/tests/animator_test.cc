#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entities/animator.h"

using ::testing::HasSubstr;

namespace engine::entities::tests {

class AnimatorTest : public testing::Test {
 protected:
  std::string console_output;

  void SetUp() override {
    // Arrange
    testing::internal::CaptureStderr();
  }

  Animator GetDefaultValidAnimator() {
    return Animator{"", 4, {32, 32}};
  }
};

TEST_F(AnimatorTest, SpritesInSheetInvalidIntegerSqrtError) {
  // Act
  Animator animator("", 3, {32, 32});
  console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_THAT(console_output, HasSubstr("sprites_in_sheet does not translate to an equal amount of rows and columns"));
}

TEST_F(AnimatorTest, SpritesInSheetValidIntegerSqrtNoError) {
  // Act
  Animator animator(GetDefaultValidAnimator());
  console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_EQ(console_output, "");
}

TEST_F(AnimatorTest, SetCurrentAnimationSpriteSheetInvalidIndexError) {
  // Act
  Animator animator(GetDefaultValidAnimator());
  animator.SetCurrentAnimationSpriteSheet(1000); // Index does not exist
  console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_THAT(console_output, HasSubstr("Animator: No valid sprite sheet at index"));
}

TEST_F(AnimatorTest, SetCurrentAnimationSpriteSheetValidIndexNoError) {
  // Act
  Animator animator(GetDefaultValidAnimator());
  int insert_index = 1;
  animator.SetSpriteSheetAtIndex("", insert_index);
  animator.SetCurrentAnimationSpriteSheet(insert_index); // Index does not exist
  console_output = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_EQ(console_output, "");
}

}