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

    before_object_count_ = GameObject::GetAllSceneObjects().size();
    empty_game_object_ = GameObject::Create();
  }

  void TearDown() override {
    SceneManager::GetInstance().RemoveScene(test_scene_name_);
    SceneManager::GetInstance().RemoveScene(switchable_scene_name_);
  }

  static Scene* CreateTestScene() {
    Scene* scene = new Scene();

    auto enemy_child = GameObject::Create();
    enemy_child->SetTagName("EnemyChild");
    enemy_child->SetName("EnemyChildName");

    auto enemy1 = GameObject::Create();
    enemy1->SetTagName("Enemy");
    enemy1->AddChildObject(enemy_child);

    auto enemy2 = GameObject::Create();
    enemy2->SetTagName("Enemy");
    enemy2->AddChildObject(enemy_child);

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
  int after_object_count = GameObject::GetAllSceneObjects().size();

  // Assert
  ASSERT_EQ(after_object_count, before_object_count_+1);
}

TEST_F(SceneTest, SceneRemoveObjectCountDecreased) {
  // Act
  active_scene_->AddObject(empty_game_object_);
  int before_object_count = GameObject::GetAllSceneObjects().size();
  GameObject::RemoveSceneObject(empty_game_object_);
  int after_object_count = GameObject::GetAllSceneObjects().size();

  // Assert
  ASSERT_EQ(after_object_count, before_object_count-1);
}

TEST_F(SceneTest, SceneRemoveObjectNotInSceneCountNotDecreased) {
  // Act
  GameObject::RemoveSceneObject(empty_game_object_);
  int after_object_count = GameObject::GetAllSceneObjects().size();

  // Assert
  ASSERT_EQ(after_object_count, before_object_count_);
}

TEST_F(SceneTest, SceneGetObjectsByTagNameValid) {
  // Act
  auto objects = GameObject::GetSceneObjectsByTagName("Enemy");

  // Assert
  ASSERT_EQ(objects.size(), 2);
}

TEST_F(SceneTest, SceneGetObjectsByTagNameInvalid) {
  // Act
  auto objects = GameObject::GetSceneObjectsByTagName("DoesntExist");

  // Assert
  ASSERT_EQ(objects.size(), 0);
}

TEST_F(SceneTest, SceneGetChildObjectsByTagNameValid) {
  // Act
  auto child_objects = GameObject::GetSceneObjectsByTagName("EnemyChild", true);

  // Assert
  ASSERT_EQ(child_objects.size(), 1);
}

TEST_F(SceneTest, SceneGetChildObjectsByTagNameInvalid) {
  // Act
  auto child_objects = GameObject::GetSceneObjectsByTagName("DoesntExist");

  // Assert
  ASSERT_EQ(child_objects.size(), 0);
}

TEST_F(SceneTest, SceneGetObjectsByNameValid) {
  // Act
  auto object = GameObject::GetSceneObjectByName("Player");

  // Assert
  ASSERT_NE(object, nullptr);
  ASSERT_EQ(object->GetName(), "Player");
}

TEST_F(SceneTest, SceneGetObjectsByNameInvalid) {
  // Act
  auto object = GameObject::GetSceneObjectByName("DoesntExist");

  // Assert
  ASSERT_EQ(object, nullptr);
}

TEST_F(SceneTest, SceneGetChildObjectsByNameValid) {
  // Act
  auto child_object = GameObject::GetSceneObjectByName("EnemyChildName", true);

  // Assert
  ASSERT_NE(child_object, nullptr);
  ASSERT_EQ(child_object->GetName(), "EnemyChildName");
}

TEST_F(SceneTest, SceneGetChildObjectsByNameInvalid) {
  // Act
  auto child_object = GameObject::GetSceneObjectByName("DoesntExist", true);

  // Assert
  ASSERT_EQ(child_object, nullptr);
}

TEST_F(SceneTest, SwitchSceneZeroObjectsInitially) {
  // Act
  SceneManager::GetInstance().SetActiveScene(switchable_scene_name_);
  auto objects = GameObject::GetAllSceneObjects();

  // Assert
  ASSERT_EQ(objects.size(), 0);
}

TEST_F(SceneTest, SwitchSceneWithObjectsValid) {
  // Act
  auto current_scene_objects = GameObject::GetAllSceneObjects();
  int current_scene_object_count = current_scene_objects.size();
  SceneManager::GetInstance().SetActiveScene(switchable_scene_name_, current_scene_objects);
  auto new_scene_objects = GameObject::GetAllSceneObjects();
  int new_scene_object_count = new_scene_objects.size();

  // Assert
  ASSERT_EQ(current_scene_object_count, new_scene_object_count);
}

}