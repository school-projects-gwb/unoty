#include <iostream>
#include <utility>
#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "engine/renderer.h"
#include "entities/sprite.h"
#include "entities/structs/key.h"
#include "entities/behaviour_script.h"
#include "engine/physics.h"
#include "entities/animator.h"

namespace engine::entities {

class Scene::Impl {
 public:
  Impl() {
    background_ = std::make_unique<SceneBackground>();
    camera_ = std::make_unique<Camera>();
  }

  void AddObject(std::shared_ptr<GameObject> object) {
    // Insert new GameObject at position based on its layer
    // Makes sure objects get rendered in correct order of their layers
    auto insert_position = std::lower_bound(game_objects_.begin(), game_objects_.end(), object,
                                            [](const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) {
                                        return a->GetLayer() < b->GetLayer();
                                      });

    game_objects_.insert(insert_position, std::move(object));
  }

  void InitialiseObjects() {
    for (const auto& game_object : game_objects_) {
      auto behaviour_scripts = game_object->GetComponentsByType<entities::BehaviourScript>();
      for (const auto& script : behaviour_scripts) {
        script->OnStart();
      }
    }
  }
  
  void UpdatePhysics(const std::unique_ptr<physics::Physics>& physics) {
    // todo implement
  }

  void TriggerListeners(const std::set<entities::Key>& keys) {
    for (const auto& game_object : game_objects_) {
      auto behaviour_scripts = game_object->GetComponentsByType<entities::BehaviourScript>();
      for (const auto& script : behaviour_scripts) {
        for (const auto& key : keys)
          script->OnInput(key);

        script->OnUpdate();
      }
    }
  }

  void RenderObjects(const std::unique_ptr<ui::Renderer>& renderer) {
    renderer->StartRenderFrame();
    camera_->UpdatePosition();
    renderer->UpdateCameraPosition(camera_.get());

    background_->RenderBackground(renderer);

    for (const auto& game_object : game_objects_) {
      auto sprite_components = game_object->GetComponentsByType<Sprite>();
      for (const auto& sprite : sprite_components)
        sprite->Render(renderer, sprite->GetGameObject()->GetTransform());

      auto animator_components = game_object->GetComponentsByType<Animator>();
      for (const auto& animator : animator_components)
        animator->Render(renderer, animator->GetGameObject()->GetTransform());
    }

    renderer->EndRenderFrame();
  }

  void SetCamera(std::unique_ptr<Camera> &camera) {
    camera_ = std::move(camera);
  }

  void SetBackground(std::unique_ptr<SceneBackground>& scene_background) {
    background_ = std::move(scene_background);
  }

  std::shared_ptr<GameObject> GetObjectByName(const std::string &name) {
    // todo implement
    return nullptr;
  }

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string &tag_name) {
    // todo implement
    return {};
  }

 private:
  std::vector<std::shared_ptr<GameObject>> game_objects_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<SceneBackground> background_;
};

Scene::Scene() : impl_(new Impl()) {}
Scene::~Scene() = default;

void Scene::AddObject(std::shared_ptr<GameObject> object) {
  impl_->AddObject(std::move(object));
}

void Scene::InitialiseObjects() {
  impl_->InitialiseObjects();
}

void Scene::TriggerListeners(const std::set<entities::Key>& keys) {
  impl_->TriggerListeners(keys);
}

void Scene::UpdatePhysics(const std::unique_ptr<physics::Physics>& physics) {
  impl_->UpdatePhysics(physics);
}

void Scene::RenderObjects(const std::unique_ptr<ui::Renderer>& renderer) {
  impl_->RenderObjects(renderer);
}

void Scene::SetCamera(std::unique_ptr<Camera> camera) {
  impl_->SetCamera(camera);
}

void Scene::SetBackground(std::unique_ptr<SceneBackground> scene_background) {
  impl_->SetBackground(scene_background);
}

std::shared_ptr<GameObject> Scene::GetObjectByName(const std::string &name) {
  return impl_->GetObjectByName(name);
}

std::vector<std::shared_ptr<GameObject>> Scene::GetObjectsByTagName(const std::string &tag_name) {
  return impl_->GetObjectsByTagName(tag_name);
}

}