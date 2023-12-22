#include <iostream>
#include <utility>
#include <unordered_set>
#include <functional>

#include "entities/scene/scene.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "physics/physics_engine.h"
#include "entities/animator.h"
#include "scene_object_registry.h"
#include "entities/ui/ui_object.h"
#include "entities/particle_emitters/particle_emitter.h"
#include "engine/engine_config.h"
#include "entities/light_source.h"
#include "entities/listeners/gamepad_listener.h"

namespace engine::entities {

class Scene::Impl {
 public:
  using RenderCallback = std::function<void(const std::unique_ptr<ui::Renderer> &renderer,
                                            const std::shared_ptr<GameObject> &game_object)>;

  Impl() {
    viewport_rendering_ = false;
    background_ = std::make_unique<SceneBackground>();
    lighting_ = std::make_unique<SceneLighting>();
    camera_ = std::make_unique<Camera>();
    object_registry_ = std::make_unique<SceneObjectRegistry>();
  }

  void SetSceneName(const std::string &scene_name) {
    if (scene_name_.empty()) scene_name_ = scene_name;
  }

  const std::string &GetSceneName() {
    return scene_name_;
  }

  void AddObject(std::shared_ptr<GameObject> object) {
    object_registry_->AddObject(std::move(object));
  }

  void QueueObject(std::shared_ptr<GameObject> object) {
    object_registry_->QueueObject(std::move(object));
  }

  void RemoveObject(std::shared_ptr<GameObject> object) {
    object_registry_->RemoveObject(std::move(object));
  }

  void AddListener(std::shared_ptr<Listener> listener) {
    object_registry_->AddListener(std::move(listener));
  }

  void InitialiseObjects() {
    for (const auto &game_object : object_registry_->GetObjects())
      TriggerBehaviourScriptOnStartRecursive(game_object);

    for (const auto &game_object : object_registry_->GetObjects())
      for (auto rigid_body : game_object->GetComponentsByType<RigidBody>())
        rigid_body->Register();

    if (background_music_ != nullptr && background_music_->play_on_wake_) background_music_->Play();
  }

  void UpdatePhysics(const std::unique_ptr<physics::PhysicsEngine> &physics) {
    physics->ExecutePhysicsStep();
    auto colliding_objects = physics->GetContactObjects(true);

    for (auto colliding_object_pair : colliding_objects) {
      for (const auto &script : colliding_object_pair.second->GetComponentsByType<BehaviourScript>())
        script->OnCollisionEnter(colliding_object_pair.first);
      for (const auto &script : colliding_object_pair.first->GetComponentsByType<BehaviourScript>())
        script->OnCollisionEnter(colliding_object_pair.second);
    }

    auto lost_contact_objects = physics->GetContactObjects(false);

    for (auto colliding_object_pair : lost_contact_objects) {
      for (const auto &script : colliding_object_pair.second->GetComponentsByType<BehaviourScript>())
        script->OnCollisionExit(colliding_object_pair.first);
      for (const auto &script : colliding_object_pair.first->GetComponentsByType<BehaviourScript>())
        script->OnCollisionExit(colliding_object_pair.second);
    }

    physics->FinalizePhysicsStep();
  }

  void TriggerListeners() {
    for (const auto &game_object : object_registry_->GetObjects())
      if (game_object->GetIsReady())
        TriggerBehaviourScriptsRecursive(game_object);

    for (const auto &key_listener : object_registry_->GetListenersByType<KeyListener>()) {
      if (!Input::GetPressedKeys().empty()) key_listener->OnKeyPressed();
      if (!Input::GetReleasedKeys().empty()) key_listener->OnKeyReleased();
    }

    for (const auto &mouse_listener : object_registry_->GetListenersByType<MouseListener>()) {
      if (Input::IsMouseMoved()) mouse_listener->OnMouseMoved();
      if (Input::IsMousePressed()) mouse_listener->OnMousePressed();
      if (Input::IsMouseReleased()) mouse_listener->OnMouseReleased();
      if (Input::IsMouseClicked()) mouse_listener->OnMouseClicked();
    }

    for (const auto &gamepad_listener : object_registry_->GetListenersByType<GamepadListener>()) {
      if (Input::IsLeftStickMoved()) gamepad_listener->OnLeftStickMoved();
      if (Input::IsRightStickMoved()) gamepad_listener->OnRightStickMoved();
      if (!Input::GetPressedGamepadButtons().empty()) gamepad_listener->OnButtonPressed();
      if (!Input::GetReleasedGamepadButtons().empty()) gamepad_listener->OnButtonPressed();
    }
  }

  void DequeueObjects() {
    for (const auto &game_object : object_registry_->GetQueuedObjects()) {
      if (game_object->GetIsActive()) {
        TriggerBehaviourScriptOnWakeRecursive(game_object);
        game_object->SetReadyTrue();
      }
      object_registry_->DequeueObject(game_object);
    }
  }

  void RenderObjects(const std::unique_ptr<ui::Renderer> &renderer) {
    camera_->UpdatePosition();
    renderer->UpdateCameraPosition(camera_.get());
    background_->RenderBackground(renderer);
    auto game_objects = object_registry_->GetObjects();

    // Process rendering for all objects and their child objects recursively
    for (const auto &game_object : viewport_rendering_ ? FilterObjectsInView(game_objects) : game_objects)
      if (game_object->GetIsReady())
        RenderObjectsRecursive(renderer,
                               game_object,
                               [this](const std::unique_ptr<ui::Renderer> &renderer,
                                      const std::shared_ptr<GameObject> &game_object) {
                                 RenderGameObject(renderer,
                                                  game_object);
                               });

    lighting_->StartRenderLighting(renderer->GetSpriteRenderer());

    for (const auto &game_object : game_objects)
      if (game_object->GetIsReady())
        RenderObjectsRecursive(renderer,
                               game_object,
                               [this](const std::unique_ptr<ui::Renderer> &renderer,
                                      const std::shared_ptr<GameObject> &game_object) {
                                 RenderLightObject(renderer,
                                                   game_object);
                               });

    renderer->GetSpriteRenderer()->EndRenderFrame();

    for (const auto &game_object : game_objects)
      if (game_object->GetIsReady())
        RenderObjectsRecursive(renderer,
                               game_object,
                               [this](const std::unique_ptr<ui::Renderer> &renderer,
                                      const std::shared_ptr<GameObject> &game_object) {
                                 RenderUiObject(renderer,
                                                game_object);
                               });
  }

  static void RenderDebug(const std::unique_ptr<ui::Renderer> &renderer, const entities::DebugInfo &debug_info) {
    ui::TextRenderInfo render_info{debug_info.font_path, 12, "FPS: " + std::to_string(debug_info.most_recent_fps),
                                   Vector2d{50, 25}, ElementPosition::TopRight};

    renderer->GetTextRenderer()->RenderText(render_info);
    renderer->GetSpriteRenderer()->RenderDebugRectangles(debug_info.debug_rectangles);
  }

  void SetCamera(std::unique_ptr<Camera> &camera) {
    camera_ = std::move(camera);
  }

  [[nodiscard]] const Point GetCameraPosition(bool with_offset) const {
    return camera_->GetPosition(with_offset);
  }

  void SetBackground(std::unique_ptr<SceneBackground> &scene_background) {
    background_ = std::move(scene_background);
  }

  void SetLighting(std::unique_ptr<SceneLighting> &scene_lighting) {
    lighting_ = std::move(scene_lighting);
  }

  [[nodiscard]] const std::unique_ptr<SceneLighting> &GetLighting() const {
    return lighting_;
  }

  void SetBackgroundMusic(std::unique_ptr<AudioSource> &music) {
    background_music_ = std::move(music);
  }

  std::shared_ptr<GameObject> GetObjectByName(const std::string &name, bool search_recursive = false) {
    return object_registry_->GetObjectByName(name, search_recursive);
  }

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string &tag_name,
                                                               bool search_recursive = false) {
    return object_registry_->GetObjectsByTagName(tag_name, search_recursive);
  }

  std::vector<std::shared_ptr<GameObject>> GetObjects() {
    return object_registry_->GetObjects();
  }

  void ClearAllObjects() {
    object_registry_->Reset();
  }

  void SetViewportRendering(bool viewport_rendering) {
    viewport_rendering_ = viewport_rendering;
  }

  void SetViewportRendering(bool viewport_rendering, float offset) {
    SetViewportRendering(viewport_rendering);
    viewport_offset_ = offset;
  }

 private:
  std::unique_ptr<SceneObjectRegistry> object_registry_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<SceneBackground> background_;
  std::unique_ptr<SceneLighting> lighting_;
  std::unique_ptr<AudioSource> background_music_ = nullptr;
  std::string scene_name_;
  bool viewport_rendering_;
  float viewport_offset_{};

  std::vector<std::shared_ptr<GameObject>> FilterObjectsInView(const std::vector<std::shared_ptr<GameObject>> &game_objects) {
    std::vector<std::shared_ptr<GameObject>> objects_in_view;

    for (const auto &object : game_objects)
      if (ProcessInViewCheck(object))
        objects_in_view.push_back(object);

    return objects_in_view;
  }

  bool ProcessInViewCheck(const std::shared_ptr<GameObject> &object) {
    for (const auto &child : object->GetChildObjects())
      if (ProcessInViewCheck(child))
        return true;

    return CheckIfObjectInView(object);
  }

  bool CheckIfObjectInView(const std::shared_ptr<GameObject> &object) {
    auto object_transform = object->GetTransform();
    auto object_size = object_transform->GetScaledSize();

    if (dynamic_cast<UiObject *>(object.get())) return true;
    if (object_size.x <= 0 || object_size.y <= 0) return true;
    if (camera_->IsObjectInViewport(object_transform, viewport_offset_, camera_->GetPosition(true))) return true;
    if (CheckEmitterInView(object)) return true;

    return false;
  }

  bool CheckEmitterInView(const std::shared_ptr<GameObject> &object) {
    auto emitter = object->GetComponentByType<ParticleEmitter>();
    if (emitter == nullptr) return false;

    for (const auto &particle : emitter->GetParticles())
      if (camera_->IsObjectInViewport(particle->GetTransform(), viewport_offset_, camera_->GetPosition(true)))
        return true;

    return false;
  }

  void RenderObjectsRecursive(const std::unique_ptr<ui::Renderer> &renderer,
                              const std::shared_ptr<GameObject> &game_object,
                              RenderCallback render_callback) {
    render_callback(renderer, game_object);

    for (const auto &child_object : game_object->GetChildObjects())
      if (child_object->GetIsReady()) RenderObjectsRecursive(renderer, child_object, render_callback);
  }

  void TriggerBehaviourScriptsRecursive(const std::shared_ptr<GameObject> &game_object) {
    for (const auto &script : game_object->GetComponentsByType<entities::BehaviourScript>()) {
      script->OnInput();
      script->OnUpdate();
    }

    for (const auto &child_object : game_object->GetChildObjects()) {
      if (child_object->GetIsReady())
        TriggerBehaviourScriptsRecursive(child_object);
    }
  }

  void TriggerBehaviourScriptOnWakeRecursive(const std::shared_ptr<GameObject> &game_object) {
    for (const auto &script : game_object->GetComponentsByType<entities::BehaviourScript>())
      script->OnWake();

    for (const auto &child_object : game_object->GetChildObjects()) {
      if (child_object->GetIsReady())
        TriggerBehaviourScriptOnWakeRecursive(child_object);
    }
  }

  void TriggerBehaviourScriptOnStartRecursive(const std::shared_ptr<GameObject> &game_object) {
    for (const auto &script : game_object->GetComponentsByType<entities::BehaviourScript>())
      script->OnStart();

    for (const auto &child_object : game_object->GetChildObjects()) {
      if (child_object->GetIsReady())
        TriggerBehaviourScriptOnStartRecursive(child_object);
    }
  }

  void RenderGameObject(const std::unique_ptr<ui::Renderer> &renderer, std::shared_ptr<GameObject> game_object) {
    for (const auto &sprite : game_object->GetComponentsByType<Sprite>())
      sprite->Render(renderer->GetSpriteRenderer(), game_object->GetTransform());

    for (const auto &animator : game_object->GetComponentsByType<Animator>())
      animator->Render(renderer->GetSpriteRenderer(), game_object->GetTransform());

    for (const auto &particle_emitter : game_object->GetComponentsByType<ParticleEmitter>())
      particle_emitter->Render(renderer->GetSpriteRenderer(), game_object->GetTransform());
  }

  void RenderUiObject(const std::unique_ptr<ui::Renderer> &renderer, std::shared_ptr<GameObject> game_object) {
    if (auto ui_object = std::dynamic_pointer_cast<UiObject>(game_object))
      ui_object->Render(renderer);
  }

  void RenderLightObject(const std::unique_ptr<ui::Renderer> &renderer, std::shared_ptr<GameObject> game_object) {
    for (const auto &light_source : game_object->GetComponentsByType<LightSource>())
      light_source->Render(renderer->GetSpriteRenderer(), game_object->GetTransform());
  }
};

Scene::Scene() : impl_(new Impl()) {}
Scene::~Scene() = default;

void Scene::SetSceneName(const std::string &scene_name) {
  impl_->SetSceneName(scene_name);
}

const std::string &Scene::GetSceneName() {
  return impl_->GetSceneName();
}

void Scene::AddObject(std::shared_ptr<GameObject> object) {
  impl_->AddObject(std::move(object));
}

void Scene::QueueObject(std::shared_ptr<GameObject> object) {
  impl_->QueueObject(std::move(object));
}

void Scene::AddListener(std::shared_ptr<Listener> listener) {
  impl_->AddListener(std::move(listener));
}

void Scene::RemoveObject(std::shared_ptr<GameObject> object_to_remove) {
  impl_->RemoveObject(std::move(object_to_remove));
}

void Scene::InitialiseObjects() {
  impl_->InitialiseObjects();
}

void Scene::TriggerListeners() {
  impl_->TriggerListeners();
}

void Scene::DequeueObjects() {
  impl_->DequeueObjects();
}

void Scene::UpdatePhysics(const std::unique_ptr<physics::PhysicsEngine> &physics) {
  impl_->UpdatePhysics(physics);
}

void Scene::RenderObjects(const std::unique_ptr<ui::Renderer> &renderer) {
  impl_->RenderObjects(renderer);
}

void Scene::RenderDebug(const std::unique_ptr<ui::Renderer> &renderer, const entities::DebugInfo &debug_info) {
  impl_->RenderDebug(renderer, debug_info);
}

void Scene::SetCamera(std::unique_ptr<Camera> camera) {
  impl_->SetCamera(camera);
}

const Point Scene::GetCameraPosition(bool with_offset) const {
  return impl_->GetCameraPosition(with_offset);
}

void Scene::SetBackground(std::unique_ptr<SceneBackground> scene_background) {
  impl_->SetBackground(scene_background);
}

void Scene::SetLighting(std::unique_ptr<SceneLighting> scene_lighting) {
  impl_->SetLighting(scene_lighting);
}

const std::unique_ptr<SceneLighting> &Scene::GetLighting() const {
  return impl_->GetLighting();
}

void Scene::SetBackgroundMusic(std::unique_ptr<AudioSource> music) {
  impl_->SetBackgroundMusic(music);
}

std::shared_ptr<GameObject> Scene::GetObjectByName(const std::string &name, bool search_recursive) {
  return impl_->GetObjectByName(name, search_recursive);
}

std::vector<std::shared_ptr<GameObject>> Scene::GetObjectsByTagName(const std::string &tag_name,
                                                                    bool search_recursive) {
  return impl_->GetObjectsByTagName(tag_name, search_recursive);
}

std::vector<std::shared_ptr<GameObject>> Scene::GetAllObjects() {
  return impl_->GetObjects();
}

void Scene::ClearAllObjects() {
  impl_->ClearAllObjects();
}

void Scene::SetViewportRendering(bool viewport_rendering) {
  impl_->SetViewportRendering(viewport_rendering);
}

void Scene::SetViewportRendering(bool viewport_rendering, float offset) {
  impl_->SetViewportRendering(viewport_rendering, offset);
}

}