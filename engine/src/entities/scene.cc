#include <iostream>
#include <utility>
#include "../include/entities/scene.h"
#include "entities/game_object.h"
#include "engine/renderer.h"
#include "entities/sprite.h"
#include "entities/structs/key.h"
#include "entities/behaviour_script.h"
#include "engine/physics.h"

namespace engine::entities {

class Scene::Impl {
 public:
  Impl() {}

  void AddObject(std::shared_ptr<GameObject> object) {
    game_objects_.emplace_back(std::move(object));
  }
  
  void UpdatePhysics(const std::unique_ptr<physics::Physics>& physics) {
    // todo implement
  }

  void TriggerInputs(const entities::Key& key) {
    if (key == Key::None) return;

    for (const auto& game_object : game_objects_) {
      auto behaviour_scripts = game_object->GetComponentsByType<entities::BehaviourScript>();
      for (const auto& script : behaviour_scripts) script->OnInput(key);
    }
  }

  void RenderObjects(const std::unique_ptr<ui::Renderer>& renderer) {
    renderer->UpdateCameraPosition(camera_.get());

    for (const auto& game_object : game_objects_) {
      auto sprite_components = game_object->GetComponentsByType<Sprite>();
      for (const auto& sprite : sprite_components) {
        sprite->Render(renderer, sprite->GetGameObject()->GetTransform().Position);
      }
    }
  }

  void SetCamera(std::unique_ptr<Camera> &camera) {
    camera_ = std::move(camera);
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
  std::unique_ptr<entities::Camera> camera_;
};

Scene::Scene() : impl_(new Impl()) {}
Scene::~Scene() = default;

void Scene::AddObject(std::shared_ptr<GameObject> object) {
  impl_->AddObject(std::move(object));
}

void Scene::TriggerInputs(const entities::Key &key) {
  impl_->TriggerInputs(key);
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

std::shared_ptr<GameObject> Scene::GetObjectByName(const std::string &name) {
  return impl_->GetObjectByName(name);
}

std::vector<std::shared_ptr<GameObject>> Scene::GetObjectsByTagName(const std::string &tag_name) {
  return impl_->GetObjectsByTagName(tag_name);
}

}