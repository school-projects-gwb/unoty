#include <gtest/gtest.h>
#include "entities/transform.h"
#include "entities/camera.h"

namespace engine::entities::tests {

class GameObjectTestTest : public testing::Test {
 protected:
  std::shared_ptr<GameObject> game_object_;
  std::shared_ptr<GameObject> child_object_;
  void SetUp() override {
    // Arrange
    game_object_ = GameObject::Create();
    child_object_ = GameObject::Create();
  }
};

TEST_F(GameObjectTestTest, AddChildParentIsNotNull) {
  // Arrange

  // Act
  game_object_->AddChildObject(child_object_);

  // Assert
  EXPECT_NE(child_object_->GetParent(), nullptr);
}

TEST_F(GameObjectTestTest, RemoveChildParentIsNull) {
  // Arrange
  game_object_->AddChildObject(child_object_);
  bool before_is_nullptr = child_object_->GetParent() == nullptr;

  // Act
  game_object_->RemoveChildObject(child_object_);

  // Assert
  EXPECT_EQ(before_is_nullptr, false);
  EXPECT_EQ(child_object_->GetParent(), nullptr);
}

}