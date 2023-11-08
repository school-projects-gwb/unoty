#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entities/scene/scene.h"
#include "entities/scene/scene_manager.h"

namespace engine::entities::tests {

class SceneTest : public testing::Test {
 protected:
  std::shared_ptr<Scene> active_scene_;
  std::shared_ptr<Scene> switchable_scene_;
  int before_object_count_ = 0;
  std::shared_ptr<GameObject> empty_game_object_;
  std::string test_scene_name_ = "test";
  std::string switchable_scene_name_ = "switch";

  void SetUp() override {
    // Arrange
    SceneManager::GetInstance().AddScene(test_scene_name_, CreateTestScene);
    SceneManager::GetInstance().AddScene(switchable_scene_name_, CreateTestSwitchableScene);

    SceneManager::GetInstance().SetActiveScene(test_scene_name_);

    active_scene_ = SceneManager::GetInstance().GetActiveScene();

    before_object_count_ = GameObject::GetAllObjects().size();
    empty_game_object_ = GameObject::Create();
  }

  void TearDown() override {
    SceneManager::GetInstance().RemoveScene(test_scene_name_);
    SceneManager::GetInstance().RemoveScene(switchable_scene_name_);
  }

  static Scene* CreateTestScene() {
    Scene* scene = new Scene();

    auto enemy1 = GameObject::Create();
    enemy1->SetTagName("Enemy");

    auto enemy2 = GameObject::Create();
    enemy2->SetTagName("Enemy");

    auto player = GameObject::Create();
    player->SetName("Player");

    scene->AddObject(enemy1);
    scene->AddObject(enemy2);
    scene->AddObject(player);

    return scene;
  }

  static Scene* CreateTestSwitchableScene() {
    return new Scene();
  }
};

TEST_F(SceneTest, SceneAddObjectCountIncreased) {
  // Act
  active_scene_->AddObject(empty_game_object_);
  int after_object_count = GameObject::GetAllObjects().size();

  // Assert
  ASSERT_EQ(after_object_count, before_object_count_+1);
}

TEST_F(SceneTest, SceneRemoveObjectCountDecreased) {
  // Act
  active_scene_->AddObject(empty_game_object_);
  int before_object_count = GameObject::GetAllObjects().size();
  GameObject::RemoveObject(empty_game_object_);
  int after_object_count = GameObject::GetAllObjects().size();

  // Assert
  ASSERT_EQ(after_object_count, before_object_count-1);
}

TEST_F(SceneTest, SceneRemoveObjectNotInSceneCountNotDecreased) {
  // Act
  GameObject::RemoveObject(empty_game_object_);
  int after_object_count = GameObject::GetAllObjects().size();

  // Assert
  ASSERT_EQ(after_object_count, before_object_count_);
}

TEST_F(SceneTest, SceneGetObjectsByTagNameValid) {
  // Act
  auto objects = GameObject::GetObjectsByTagName("Enemy");

  // Assert
  ASSERT_EQ(objects.size(), 2);
}

TEST_F(SceneTest, SceneGetObjectsByTagNameInvalid) {
  // Act
  auto objects = GameObject::GetObjectsByTagName("DoesntExist");

  // Assert
  ASSERT_EQ(objects.size(), 0);
}

TEST_F(SceneTest, SceneGetObjectsByNameValid) {
  // Act
  auto object = GameObject::GetObjectByName("Player");

  // Assert
  ASSERT_NE(object, nullptr);
  ASSERT_EQ(object->GetName(), "Player");
}

TEST_F(SceneTest, SceneGetObjectsByNameInvalid) {
  // Act
  auto object = GameObject::GetObjectByName("DoesntExist");

  // Assert
  ASSERT_EQ(object, nullptr);
}

TEST_F(SceneTest, SwitchSceneZeroObjectsInitially) {
  // Act
  SceneManager::GetInstance().SetActiveScene(switchable_scene_name_);
  auto objects = GameObject::GetAllObjects();

  // Assert
  ASSERT_EQ(objects.size(), 0);
}

TEST_F(SceneTest, SwitchSceneWithObjectsValid) {
  // Act
  auto current_scene_objects = GameObject::GetAllObjects();
  int current_scene_object_count = current_scene_objects.size();
  SceneManager::GetInstance().SetActiveScene(switchable_scene_name_, current_scene_objects);
  auto new_scene_objects = GameObject::GetAllObjects();
  int new_scene_object_count = new_scene_objects.size();

  // Assert
  ASSERT_EQ(current_scene_object_count, new_scene_object_count);
}

}