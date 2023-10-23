#include <iostream>
#include <utility>
#include "../include/entities/scene.h"
#include "entities/game_object.h"

namespace engine::entities {

class Scene::Impl {
 public:
  Impl() {
    std::cout << "Scene created";
  }

  void AddObject(std::shared_ptr<GameObject> object) {
    game_objects_.emplace_back(std::move(object));
  }
  
  void UpdateObjects() {
    // todo: implement logic
  }

  void RenderObjects() {
    // todo: implement logic
  }

 private:
  std::vector<std::shared_ptr<GameObject>> game_objects_;
};

Scene::Scene() : impl_(new Impl()) {}
Scene::~Scene() = default;

void Scene::AddGameObject(std::shared_ptr<GameObject> object) {
  impl_->AddObject(std::move(object));
}

void Scene::UpdateObjects() {
  impl_->UpdateObjects();
}

void Scene::RenderObjects() {
  impl_->RenderObjects();
}

}