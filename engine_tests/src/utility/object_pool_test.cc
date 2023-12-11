#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entities/animator.h"
#include "utility/object_pool.h"

namespace engine::entities::tests {

class TestObject : public GameObject {
 public:
  bool is_active = false;
};

class ObjectPoolTest : public testing::Test {
 protected:
  std::unique_ptr<utility::ObjectPool<TestObject>> object_pool_;

  void SetUp() override {
    // Arrange
    object_pool_ = std::make_unique<utility::ObjectPool<TestObject>>(AcquireCallback, ReleaseCallback, []() {});
  }

  static std::shared_ptr<TestObject> Create() {
    auto object = std::make_shared<TestObject>();
    return object;
  }

  static std::shared_ptr<TestObject> AcquireCallback(std::vector<std::weak_ptr<TestObject>> objects) {
    for (const auto& weak_object : objects) {
      auto object = weak_object.lock();
      if (!object) continue;

      if (!object->is_active) return object;
    }

    return nullptr;
  }

  static void ReleaseCallback(std::shared_ptr<TestObject> obj) { obj->is_active = false; }
};

TEST_F(ObjectPoolTest, ObjectPoolEmptyReturnsNullptr) {
  // Act
  auto retrieved_object = object_pool_->Acquire();

  // Assert
  ASSERT_EQ(retrieved_object, nullptr);
}

}