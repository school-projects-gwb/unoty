#include <iostream>
#include <utility>
#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "rendering/renderer.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "physics/physics_engine.h"
#include "entities/animator.h"
#include "scene_object_registry.h"
#include "entities/ui/ui_object.h"
#include "entities/particle_emitter.h"

namespace engine::entities {

class Scene::Impl {
 public:
  Impl() {
    background_ = std::make_unique<SceneBackground>();
    camera_ = std::make_unique<Camera>();
    object_registry_ = std::make_unique<SceneObjectRegistry>();
  }

  void SetSceneName(const std::string& scene_name) {
    if (scene_name_.empty()) scene_name_ = scene_name;
  }

  const std::string& GetSceneName() {
    return scene_name_;
  }

  void AddObject(std::shared_ptr<GameObject> object) {
    object_registry_->AddObject(std::move(object));
  }

  void RemoveObject(std::shared_ptr<GameObject> object) {
    object_registry_->RemoveObject(std::move(object));
  }

  void AddListener(std::shared_ptr<Listener> listener) {
    object_registry_->AddListener(std::move(listener));
  }

  static void StartRenderFrame(const std::unique_ptr<ui::Renderer>& renderer) {
    renderer->StartRenderFrame();
  }

  static void EndRenderFrame(const std::unique_ptr<ui::Renderer>& renderer) {
    renderer->EndRenderFrame();
  }

  void InitialiseObjects() {
    for (const auto& game_object : object_registry_->GetObjects())
      TriggerBehaviourScriptOnStartRecursive(game_object);

    if(background_music_ != nullptr && background_music_->play_on_wake_) background_music_->Play();
  }
  
  void UpdatePhysics(const std::unique_ptr<physics::PhysicsEngine>& physics) {
    physics->ExecutePhysicsStep();
  }

  void TriggerListeners() {
    for (const auto& game_object : object_registry_->GetObjects()) {
      if (game_object->GetIsActive())
        TriggerBehaviourScriptsRecursive(game_object);
    }

    for (const auto& key_listener : object_registry_->GetListenersByType<KeyListener>()) {
      if (!Input::GetPressedKeys().empty()) key_listener->OnKeyPressed();
      if (!Input::GetReleasedKeys().empty()) key_listener->OnKeyReleased();
    }

    for (const auto& mouse_listener : object_registry_->GetListenersByType<MouseListener>()) {
      if (Input::IsMouseMoved()) mouse_listener->OnMouseMoved();
      if (Input::IsMousePressed()) mouse_listener->OnMousePressed();
      if (Input::IsMouseReleased()) mouse_listener->OnMouseReleased();
      if (Input::IsMouseClicked()) mouse_listener->OnMouseClicked();
    }
  }

  void RenderObjects(const std::unique_ptr<ui::Renderer>& renderer) {
    camera_->UpdatePosition();
    renderer->UpdateCameraPosition(camera_.get());
    background_->RenderBackground(renderer);

    // Process rendering for all objects and their child objects recursively
    for (const auto& game_object : object_registry_->GetObjects())
      if(game_object->GetIsActive()) RenderAllObjects(renderer, game_object);
  }

  static void RenderDebug(const std::unique_ptr<ui::Renderer>& renderer, const std::string& font_path, int most_recent_fps) {
    ui::TextRenderInfo render_info{font_path, 12, "FPS: " + std::to_string(most_recent_fps),
                                   Vector2d{50, 25}, ElementPosition::TopRight};
    renderer->GetTextRenderer()->RenderText(render_info);
  }

  void SetCamera(std::unique_ptr<Camera> &camera) {
    camera_ = std::move(camera);
  }

  void SetBackground(std::unique_ptr<SceneBackground>& scene_background) {
    background_ = std::move(scene_background);
  }

  void SetBackgroundMusic(std::unique_ptr<AudioSource>& music){
    background_music_ = std::move(music);
  }

  std::shared_ptr<GameObject> GetObjectByName(const std::string &name, bool search_recursive = false) {
    return object_registry_->GetObjectByName(name, search_recursive);
  }

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string &tag_name, bool search_recursive = false) {
    return object_registry_->GetObjectsByTagName(tag_name, search_recursive);
  }

  std::vector<std::shared_ptr<GameObject>> GetObjects() {
    return object_registry_->GetObjects();
  }

  void ClearAllObjects() {
    object_registry_->Reset();
  }
 private:
  std::unique_ptr<SceneObjectRegistry> object_registry_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<SceneBackground> background_;
  std::unique_ptr<AudioSource> background_music_ = nullptr;
  std::string scene_name_;

  void RenderAllObjects(const std::unique_ptr<ui::Renderer>& renderer, const std::shared_ptr<GameObject>& game_object) {
    TryRenderObject(renderer, game_object);

    for (const auto& child_object : game_object->GetChildObjects())
      if (child_object->GetIsActive()) RenderAllObjects(renderer, child_object);
  }

  void TriggerBehaviourScriptsRecursive(const std::shared_ptr<GameObject>& game_object) {
    for (const auto& script : game_object->GetComponentsByType<entities::BehaviourScript>()) {
      script->OnInput();
      script->OnUpdate();
    }

    for (const auto& child_object : game_object->GetChildObjects()) {
      if (child_object->GetIsActive())
        TriggerBehaviourScriptsRecursive(child_object);
    }
  }

  void TriggerBehaviourScriptOnStartRecursive(const std::shared_ptr<GameObject>& game_object) {
    for (const auto& script : game_object->GetComponentsByType<entities::BehaviourScript>())
      script->OnStart();

    for (const auto& child_object : game_object->GetChildObjects()) {
      if (child_object->GetIsActive())
        TriggerBehaviourScriptOnStartRecursive(child_object);
    }
  }

  void TryRenderObject(const std::unique_ptr<ui::Renderer>& renderer, std::shared_ptr<GameObject> game_object) {
    for (const auto& sprite : game_object->GetComponentsByType<Sprite>())
      sprite->Render(renderer->GetSpriteRenderer(), game_object->GetTransform());

    for (const auto& animator : game_object->GetComponentsByType<Animator>())
      animator->Render(renderer->GetSpriteRenderer(), game_object->GetTransform());

    for (const auto& particle_emitter : game_object->GetComponentsByType<ParticleEmitter>())
      particle_emitter->Render(renderer->GetSpriteRenderer(), game_object->GetTransform());

    if (auto ui_object = std::dynamic_pointer_cast<UiObject>(game_object))
      ui_object->Render(renderer);
  }
};

Scene::Scene() : impl_(new Impl()) {}
Scene::~Scene() = default;

void Scene::SetSceneName(const std::string& scene_name) {
  impl_->SetSceneName(scene_name);
}

const std::string& Scene::GetSceneName() {
  return impl_->GetSceneName();
}

void Scene::AddObject(std::shared_ptr<GameObject> object) {
  impl_->AddObject(std::move(object));
}

void Scene::AddListener(std::shared_ptr<Listener> listener) {
  impl_->AddListener(std::move(listener));
}

void Scene::RemoveObject(std::shared_ptr<GameObject> object_to_remove) {
  impl_->RemoveObject(std::move(object_to_remove));
}

void Scene::StartRenderFrame(const std::unique_ptr<ui::Renderer>& renderer) {
  impl_->StartRenderFrame(renderer);
}

void Scene::EndRenderFrame(const std::unique_ptr<ui::Renderer>& renderer) {
  impl_->EndRenderFrame(renderer);
}

void Scene::InitialiseObjects() {
  impl_->InitialiseObjects();
}

void Scene::TriggerListeners() {
  impl_->TriggerListeners();
}

void Scene::UpdatePhysics(const std::unique_ptr<physics::PhysicsEngine>& physics) {
  impl_->UpdatePhysics(physics);
}

void Scene::RenderObjects(const std::unique_ptr<ui::Renderer>& renderer) {
  impl_->RenderObjects(renderer);
}

void Scene::RenderDebug(const std::unique_ptr<ui::Renderer>& renderer, const std::string& font_path, int most_recent_fps) {
  impl_->RenderDebug(renderer, font_path, most_recent_fps);
}

void Scene::SetCamera(std::unique_ptr<Camera> camera) {
  impl_->SetCamera(camera);
}

void Scene::SetBackground(std::unique_ptr<SceneBackground> scene_background) {
  impl_->SetBackground(scene_background);
}

void Scene::SetBackgroundMusic(std::unique_ptr<AudioSource> music) {
  impl_->SetBackgroundMusic(music);
}

std::shared_ptr<GameObject> Scene::GetObjectByName(const std::string &name, bool search_recursive) {
  return impl_->GetObjectByName(name, search_recursive);
}

std::vector<std::shared_ptr<GameObject>> Scene::GetObjectsByTagName(const std::string &tag_name, bool search_recursive) {
  return impl_->GetObjectsByTagName(tag_name, search_recursive);
}

std::vector<std::shared_ptr<GameObject>> Scene::GetAllObjects() {
  return impl_->GetObjects();
}

void Scene::ClearAllObjects() {
  impl_->ClearAllObjects();
}

}