#include <filesystem>
#include "engine/engine.h"
#include "engine_tick.h"
#include "entities/scene/scene_manager.h"
#include "../rendering/sdl_renderer.h"
#include "../input/input.h"
#include "../input/sdl_input.h"
#include "engine/renderer.h"
#include "../rendering/textures/texture_registry.h"
#include "engine/physics.h"
#include "../physics/impl_physics.h"
#include "helpers/debug.h"

namespace engine {

class Engine::Impl {
 public:
  Impl() : game_tick_() {}

  static Impl& GetInstance() {
    static Impl instance;
    return instance;
  }

  void InitWithConfig(EngineConfig engine_config) {
    is_debug_mode_ = engine_config.is_debug_mode;

    renderer_ = std::make_unique<ui::SdlRenderer>(engine_config.window_width, engine_config.window_height,
                                                  engine_config.window_title);
    rendering::TextureRegistry::Initialize(renderer_);

    input_ = std::make_unique<input::SdlInput>();

    physics_ = std::make_unique<physics::ImplPhysics>();
    physics_->Initialize();

    game_tick_.Init(engine_config.game_tick_fps);
    render_tick_.Init(engine_config.render_tick_fps);

    is_config_set_ = true;
  }

  void Start() {
    while (!input_->IsWindowClosed()) {
      auto active_scene = SceneManager::GetInstance().GetActiveScene();

      if (active_scene == nullptr) {
        helpers::Debug::Error("No starting Scene set.");
        return;
      }

      if (!is_config_set_) {
        helpers::Debug::Error("No EngineConfig found. Make sure to initiate Engine with InitWithConfig.");
        return;
      }

      double delta_time = game_tick_.GetDeltaTime();
      game_tick_.AppendAccumulator(delta_time);

      while (game_tick_.GetAccumulator() >= game_tick_.GetFixedTimeStep()) {
        // Interpolation example usage for updating objects (in this case movement):
        // double factor = engine_tick_.GetAccumulator() / engine_tick_.GetFixedTimeStep();
        // double object_movement_amount = 1.0;
        // object.position += object_movement_amount * factor;
        active_scene->UpdatePhysics(physics_);
        game_tick_.SubtractAccumulator(game_tick_.GetFixedTimeStep());

        input_->ProcessInput();
        active_scene->TriggerListeners(input_->GetActiveKeys());
        if (is_debug_mode_) game_tick_.IncreaseFrameCounter();
      }

      double render_delta_time = render_tick_.GetDeltaTime();
      render_tick_.AppendAccumulator(render_delta_time);

      while (render_tick_.GetAccumulator() >= render_tick_.GetFixedTimeStep()) {
        // Interpolation example usage for rendering:
        // double render_factor = render_tick_.GetAccumulator() / render_tick_.GetFixedTimeStep();
        // Render frame using render_factor for smooth animations
        active_scene->RenderObjects(renderer_);

        render_tick_.SubtractAccumulator(render_tick_.GetFixedTimeStep());
        if (is_debug_mode_) render_tick_.IncreaseFrameCounter();
      }

      if (!is_debug_mode_) continue;

      game_tick_.IncreaseElapsed();
      render_tick_.IncreaseElapsed();
      game_tick_.ShowFps("Game update");
      render_tick_.ShowFps("Rendering");
    }

    renderer_->Exit();
  }

  void AddScene(const std::string& name, entities::SceneCallbackFunction callback_function) {
    SceneManager::GetInstance().AddScene(name, callback_function);
  }

  void SetActiveScene(const std::string& name) {
    SceneManager::GetInstance().SetActiveScene(name);
  }

  void SetActiveScene(const std::string& name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate) {
    SceneManager::GetInstance().SetActiveScene(name, std::move(objects_to_migrate));
  }
 private:
  std::unique_ptr<ui::Renderer> renderer_;
  std::unique_ptr<input::Input> input_;
  std::unique_ptr<physics::Physics> physics_;

  EngineTick game_tick_;
  EngineTick render_tick_;
  bool is_debug_mode_ = false;
  bool is_config_set_ = false;
};

Engine::Engine() : impl_(std::make_unique<Impl>()) {

}

Engine &Engine::GetInstance() {
  static Engine instance;
  return instance;
}

void Engine::InitWithConfig(engine::EngineConfig config) {
  impl_->InitWithConfig(config);
}

Engine::~Engine() = default;

void Engine::Start() {
  impl_->Start();
}

void Engine::AddScene(const std::string& scene_name, entities::SceneCallbackFunction callback_function) {
  impl_->AddScene(scene_name, callback_function);
}

void Engine::SetActiveScene(const std::string &scene_name) {
  impl_->SetActiveScene(scene_name);
}

void Engine::SetActiveScene(const std::string &scene_name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate) {
  impl_->SetActiveScene(scene_name, std::move(objects_to_migrate));
}

}