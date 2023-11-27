#include <filesystem>
#include <memory>
#include <utility>
#include "engine/engine.h"
#include "engine_tick.h"
#include "entities/scene/scene_manager.h"
#include "rendering/renderers/sdl_renderer.h"
#include "../input/input.h"
#include "../input/sdl_input.h"
#include "rendering/renderer.h"
#include "../rendering/textures/texture_registry.h"
#include "../rendering/fonts/sdl_font_registry.h"
#include "engine/physics.h"
#include "../physics/impl_physics.h"
#include "utility/debug.h"
#include "../audio/audio_factory_wrapper.h"
#include "../audio/audio_factory.h"

namespace engine {

class Engine::Impl {
 public:
  Impl() : game_tick_() {}

  static Impl& GetInstance() {
    static Impl instance;
    return instance;
  }

  void Init() {
    renderer_ = std::make_unique<ui::SdlRenderer>(EngineConfig::window_width, EngineConfig::window_height,
                                                  EngineConfig::window_title);
    rendering::TextureRegistry::Initialize(renderer_);

    audio::AudioFactoryWrapper::get_instance().SetAudioFactory(std::make_unique<audio::AudioFactory>());

    input_ = std::make_unique<input::SdlInput>();

    physics_ = std::make_unique<physics::ImplPhysics>();
    physics_->Initialize();

    game_tick_.Init(EngineConfig::game_tick_fps);

    is_config_set_ = true;
  }

  void Start() {
    if (!is_config_set_) {
      helpers::Debug::Error("No EngineConfig found. Make sure to initiate Engine with InitWithConfig.");
      return;
    }

    while (entities::Input::GetLastKeyPress() != entities::Key::UnoWindowClosed && !is_quit_game_) {
      auto active_scene = SceneManager::GetInstance().GetActiveScene();

      if (active_scene == nullptr) {
        helpers::Debug::Error("No Scene set.");
        return;
      }
      
      game_tick_.StartFrame();

      while (game_tick_.ShouldIterate()) {
        game_tick_.UpdateCurrentFrame();

        active_scene->UpdatePhysics(physics_);
        input_->ProcessInput();
        active_scene->TriggerListeners();

        active_scene->StartRenderFrame(renderer_);
        active_scene->RenderObjects(renderer_);

        if (EngineConfig::is_debug_mode)
          active_scene->RenderDebug(renderer_, EngineConfig::debug_font_path, game_tick_.GetMostRecentFps());

        active_scene->EndRenderFrame(renderer_);
      }

      if (EngineConfig::is_debug_mode)
        game_tick_.UpdateFps();
    }
  }

  void Stop() {
    is_quit_game_ = true;
  }

  void AddScene(const std::string& name, entities::SceneCallbackFunction callback_function) {
    SceneManager::GetInstance().AddScene(name, std::move(callback_function));
  }

  void SetActiveScene(const std::string& name) {
    SceneManager::GetInstance().SetActiveScene(name);
  }

  static void ToggleDebugMode() {
    EngineConfig::is_debug_mode = !EngineConfig::is_debug_mode;
  }

  bool IsDebugModeEnabled() const {
    return EngineConfig::is_debug_mode;
  }

  void SetActiveScene(const std::string& name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate) {
    SceneManager::GetInstance().SetActiveScene(name, std::move(objects_to_migrate));
  }

  void CleanupEngine() {
    audio::SdlAudioManager::Cleanup();
    renderer_->Exit();
    ui::SdlFontRegistry::Cleanup();
  }

  void SetFps(int frames_per_second) {
    game_tick_.SetTargetFps(frames_per_second);
  }
 private:
  std::unique_ptr<ui::Renderer> renderer_;
  std::unique_ptr<input::Input> input_;
  std::unique_ptr<physics::Physics> physics_;

  EngineTick game_tick_;
  bool is_config_set_ = false;
  bool is_quit_game_ = false;
};

Engine::Engine() : impl_(std::make_unique<Impl>()) {

}

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

void Engine::Stop() {
  impl_->Stop();
}

void Engine::AddScene(const std::string& scene_name, entities::SceneCallbackFunction callback_function) {
  impl_->AddScene(scene_name, callback_function);
}

void Engine::SetActiveScene(const std::string &scene_name) {
  impl_->SetActiveScene(scene_name);
}

void Engine::ToggleDebugMode() const {
  impl_->ToggleDebugMode();
}

bool Engine::IsDebugModeEnabled() const {
  return impl_->IsDebugModeEnabled();
}

void Engine::SetActiveScene(const std::string &scene_name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate) {
  impl_->SetActiveScene(scene_name, std::move(objects_to_migrate));
}

void Engine::Shutdown() {
  impl_->CleanupEngine();
  impl_.reset();
}

void Engine::SetFps(int frames_per_second) {
  impl_->SetFps(frames_per_second);
}

}