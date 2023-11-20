#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entities/animator.h"

using ::testing::HasSubstr;

namespace engine::entities::tests {

class AnimatorTest : public testing::Test {
 protected:
  std::string console_output_;

  void SetUp() override {
    // Arrange
    testing::internal::CaptureStderr();
  }

  Animator GetDefaultValidAnimator() {
    return Animator{"", 4, {32, 32}};
  }
};

TEST_F(AnimatorTest, SpritesInSheetValidIntegerSqrtNoError) {
  // Act
  Animator animator(GetDefaultValidAnimator());
  console_output_ = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_EQ(console_output_, "");
}

TEST_F(AnimatorTest, SetCurrentAnimationSpriteSheetInvalidIndexError) {
  // Act
  Animator animator(GetDefaultValidAnimator());
  animator.SetCurrentAnimationSpriteSheet(1000); // Index does not exist
  console_output_ = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_THAT(console_output_, HasSubstr("Animator: No valid sprite sheet at index"));
}

TEST_F(AnimatorTest, SetCurrentAnimationSpriteSheetValidIndexNoError) {
  // Act
  Animator animator(GetDefaultValidAnimator());
  int insert_index = 1;
  animator.SetSpriteSheetAtIndex("", insert_index);
  animator.SetCurrentAnimationSpriteSheet(insert_index); // Index does not exist
  console_output_ = testing::internal::GetCapturedStderr();

  // Assert
  EXPECT_EQ(console_output_, "");
}

}