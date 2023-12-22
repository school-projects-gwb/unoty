#include "engine/engine.h"
#include "engine_tick.h"

#include "entities/scene/scene_manager.h"
#include "rendering/renderers/sdl_renderer.h"
#include "../input/input.h"
#include "../input/sdl_input.h"
#include "rendering/renderer.h"
#include "../rendering/textures/texture_registry.h"
#include "../rendering/fonts/sdl_font_registry.h"
#include "physics/physics_engine.h"
#include "physics/box2d_physics_engine.h"
#include "utility/debug.h"
#include "../audio/audio_factory_wrapper.h"
#include "../audio/audio_factory.h"
#include "entities/structs/input.h"

namespace engine {

class Engine::Impl {
 public:
  Impl() : game_tick_() {}

  static Impl &GetInstance() {
    static Impl instance;
    return instance;
  }

  void Init() {
    renderer_ = std::make_unique<ui::SdlRenderer>(EngineConfig::window_width, EngineConfig::window_height,
                                                  EngineConfig::window_title);
    rendering::TextureRegistry::Initialize(renderer_);

    audio::AudioFactoryWrapper::GetInstance().SetAudioFactory(std::make_unique<audio::AudioFactory>());

    input_ = std::make_unique<input::SdlInput>();

    physics::PhysicsConfig physics_config{EngineConfig::game_tick_fps, 6, 2, EngineConfig::gravity};
    physics_ = std::make_unique<physics::Box2dPhysicsEngine>(physics_config);

    game_tick_.Init(EngineConfig::game_tick_fps);

    is_config_set_ = true;
  }

  void Start() {
    if (!is_config_set_) {
      utility::Debug::Error("No EngineConfig found. Make sure to initiate Engine with InitWithConfig.");
      return;
    }

    entities::DebugInfo debug_info{};
    debug_info.font_path = EngineConfig::debug_font_path;

    while (entities::Input::GetLastKeyPress() != entities::Key::UnoWindowClosed && !is_quit_game_) {
      if (EngineConfig::is_debug_mode) debug_info.debug_rectangles.clear();

      auto active_scene = SceneManager::GetInstance().GetActiveScene();

      if (active_scene == nullptr) {
        utility::Debug::Error("No Scene set.");
        return;
      }

      game_tick_.StartFrame();

      while (game_tick_.ShouldIterate()) {
        game_tick_.UpdateCurrentFrame();

        if (EngineConfig::is_paused) {
          input_->ProcessInput(active_scene->GetCameraPosition(true));
          unpause_handling_callback_();

          renderer_->StartRenderFrame();
          active_scene->RenderObjects(renderer_);
          renderer_->EndRenderFrame();

          continue;
        }

        active_scene->UpdatePhysics(physics_);
        input_->ProcessInput(active_scene->GetCameraPosition(true));

        active_scene->TriggerListeners();
        active_scene->DequeueObjects();

        renderer_->StartRenderFrame();
        active_scene->RenderObjects(renderer_);

        if (EngineConfig::is_debug_mode) {
          debug_info.most_recent_fps = game_tick_.GetMostRecentFps();
          active_scene->RenderDebug(renderer_, debug_info);
        }

        renderer_->EndRenderFrame();
      }

      if (EngineConfig::is_debug_mode)
        game_tick_.UpdateFps();
    }
  }

  void Pause(std::function<void()> unpause_handling_callback) {
    unpause_handling_callback_ = std::move(unpause_handling_callback);
    // Make sure input is reset so that it doesn't accidentally trigger anything in unpause callback logic
    entities::Input::SetLastKeyPress(entities::Key::UnoNone);
    EngineConfig::is_paused = true;
  }

  void Stop() {
    is_quit_game_ = true;
    physics_->DeregisterAllBodies();
  }

  static void AddScene(const std::string &name, entities::SceneCallbackFunction callback_function) {
    SceneManager::GetInstance().AddScene(name, std::move(callback_function));
  }

  void SetActiveScene(const std::string &name) {
    audio::SDLMixerAdapter::GetInstance()->CleanUp();
    physics_->DeregisterAllBodies();
    SceneManager::GetInstance().SetActiveScene(name);
  }

  static void ToggleDebugMode() {
    EngineConfig::is_debug_mode = !EngineConfig::is_debug_mode;
  }

  static void ToggleGodMode() {
    EngineConfig::player_god_mode = !EngineConfig::player_god_mode;
  }

  static void SetGodMode(bool value) {
    EngineConfig::player_god_mode = value;
  }

  static bool IsDebugModeEnabled() {
    return EngineConfig::is_debug_mode;
  }

  void SetActiveScene(const std::string &name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate) {
    audio::SDLMixerAdapter::GetInstance()->CleanUp();
    SceneManager::GetInstance().SetActiveScene(name, std::move(objects_to_migrate));
  }

  void CleanupEngine() {
    audio::SDLMixerAdapter::GetInstance()->CleanUp();
    renderer_->Exit();
    ui::SdlFontRegistry::Cleanup();
  }

  std::unique_ptr<physics::PhysicsEngine> &GetPhysicsEngine() {
    return physics_;
  }

  void SetFps(int frames_per_second) {
    game_tick_.SetTargetFps(frames_per_second);
    physics_->SetStepsPerSecond(frames_per_second);
  }

  void IncrementFps() {
    if (target_fps_ + 20 <= 120) target_fps_ += 20;
    else target_fps_ = 120;

    game_tick_.SetTargetFps(target_fps_);
  }

  void DecrementFps() {
    if (target_fps_ - 10 >= 10) target_fps_ -= 10;
    else target_fps_ = 10;

    game_tick_.SetTargetFps(target_fps_);
  }

  void ResetFps() {
    if (target_fps_ != 60) target_fps_ = 60;

    game_tick_.SetTargetFps(target_fps_);
  }

  static std::shared_ptr<entities::Scene> GetActiveScene() {
    return SceneManager::GetInstance().GetActiveScene();
  }

 private:
  std::unique_ptr<ui::Renderer> renderer_;
  std::unique_ptr<input::Input> input_;
  std::unique_ptr<physics::PhysicsEngine> physics_;

  EngineTick game_tick_;
  bool is_config_set_ = false;
  bool is_quit_game_ = false;
  int target_fps_ = 60;

  std::function<void()> unpause_handling_callback_;
};

Engine::Engine() : impl_(std::make_unique<Impl>()) {}

Engine &Engine::GetInstance() {
  static Engine instance;
  return instance;
}

void Engine::Init() {
  impl_->Init();
}

Engine::~Engine() = default;

void Engine::Start() {
  impl_->Start();
}

void Engine::Pause(std::function<void()> unpause_handling_callback) {
  impl_->Pause(std::move(unpause_handling_callback));
}

void Engine::Stop() {
  impl_->Stop();
}

void Engine::AddScene(const std::string &scene_name, entities::SceneCallbackFunction callback_function) {
  impl_->AddScene(scene_name, std::move(callback_function));
}

void Engine::SetActiveScene(const std::string &scene_name) {
  impl_->SetActiveScene(scene_name);
}

void Engine::ToggleDebugMode() const {
  impl_->ToggleDebugMode();
}

void Engine::ToggleGodMode() const {
  impl_->ToggleGodMode();
}

void Engine::SetGodMode(bool value) {
  impl_->SetGodMode(value);
}

bool Engine::IsDebugModeEnabled() const {
  return impl_->IsDebugModeEnabled();
}

void Engine::SetActiveScene(const std::string &scene_name,
                            std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate) {
  impl_->SetActiveScene(scene_name, std::move(objects_to_migrate));
}

void Engine::Shutdown() {
  impl_->CleanupEngine();
  impl_.reset();
}

std::unique_ptr<physics::PhysicsEngine> &Engine::GetPhysicsEngine() {
  return impl_->GetPhysicsEngine();
}

void Engine::SetFps(int frames_per_second) {
  impl_->SetFps(frames_per_second);
}

void Engine::IncrementFps() {
  impl_->IncrementFps();
}

void Engine::DecrementFps() {
  impl_->DecrementFps();
}

void Engine::ResetFps() {
  impl_->ResetFps();
}

std::shared_ptr<entities::Scene> Engine::GetActiveScene() {
  return impl_->GetActiveScene();
}

}