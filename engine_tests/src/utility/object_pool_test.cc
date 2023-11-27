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
  std::unique_ptr<ObjectPool<TestObject>> object_pool_;

  void SetUp() override {
    // Arrange
    object_pool_ = std::make_unique<ObjectPool<TestObject>>(AcquireCallback, ReleaseCallback);
  }

  static std::shared_ptr<TestObject> Create() {
    auto object = std::make_shared<TestObject>();
    return object;
  }

  static std::shared_ptr<TestObject> AcquireCallback(std::vector<std::shared_ptr<TestObject>> objects) {
    for (auto object : objects)
      if (!object->is_active) return object;

    return nullptr;
  }

  static void ReleaseCallback(std::shared_ptr<TestObject> obj) { obj->is_active = false; }
};

TEST_F(ObjectPoolTest, ObjectPoolAcquireCorrect) {
  // Act
  object_pool_->PoolObjects(10, ObjectPoolTest::Create, false);
  auto acquired_object = object_pool_->Acquire();

  // Assert
  ASSERT_NE(acquired_object, nullptr);
}

TEST_F(ObjectPoolTest, ObjectPoolReleaseCorrect) {
  // Act
  object_pool_->PoolObjects(1, ObjectPoolTest::Create, false);
  auto acquired_object = object_pool_->Acquire();
  object_pool_->Release(acquired_object);
  auto acquired_object_validation = object_pool_->Acquire();

  // Assert
  ASSERT_NE(acquired_object_validation, nullptr);
}

TEST_F(ObjectPoolTest, ObjectPoolEmptyReturnsNullptr) {
  // Act
  auto retrieved_object = object_pool_->Acquire();

  // Assert
  ASSERT_EQ(retrieved_object, nullptr);
}

}