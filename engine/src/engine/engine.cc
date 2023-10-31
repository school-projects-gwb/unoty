#include <iostream>
#include <filesystem>
#include "engine/engine.h"
#include "engine_tick.h"
#include "scene_manager.h"
#include "../rendering/sdl_renderer.h"
#include "../input/input.h"
#include "../input/sdl_input.h"
#include "engine/renderer.h"
#include "../rendering/textures/texture_registry.h"
#include "engine/physics.h"
#include "../physics/impl_physics.h"

namespace engine {

class Engine::Impl {
 public:
  explicit Impl(EngineConfig engine_config) : scene_manager_(), game_tick_() {
    is_debug_mode_ = engine_config.is_debug_mode;

    renderer_ = std::make_unique<ui::SdlRenderer>(engine_config.window_width_, engine_config.window_height_);
    rendering::TextureRegistry::Initialize(renderer_);

    input_ = std::make_unique<input::SdlInput>();

    physics_ = std::make_unique<physics::ImplPhysics>();
    physics_->Initialize();

    game_tick_.Init(engine_config.game_tick_fps);
    render_tick_.Init(engine_config.render_tick_fps);
  }

  void Start() {
    is_game_active_ = true;

    while (is_game_active_) {
      auto active_scene = scene_manager_.GetActiveScene();

      double delta_time = game_tick_.GetDeltaTime();
      game_tick_.AppendAccumulator(delta_time);

      while (game_tick_.GetAccumulator() >= game_tick_.GetFixedTimeStep()) {
        // Interpolation example usage for updating objects (in this case movement):
        // double factor = engine_tick_.GetAccumulator() / engine_tick_.GetFixedTimeStep();
        // double object_movement_amount = 1.0;
        // object.position += object_movement_amount * factor;
        active_scene->UpdatePhysics(physics_);
        game_tick_.SubtractAccumulator(game_tick_.GetFixedTimeStep());
        if (is_debug_mode_) game_tick_.IncreaseFrameCounter();
      }

      double render_delta_time = render_tick_.GetDeltaTime();
      render_tick_.AppendAccumulator(render_delta_time);

      while (render_tick_.GetAccumulator() >= render_tick_.GetFixedTimeStep()) {
        // Interpolation example usage for rendering:
        // double render_factor = render_tick_.GetAccumulator() / render_tick_.GetFixedTimeStep();
        // Render frame using render_factor for smooth animations
        input_->ProcessInput();
        active_scene->TriggerInputs(input_->GetLastKeyPress());
        active_scene->RenderObjects(renderer_);

        render_tick_.SubtractAccumulator(render_tick_.GetFixedTimeStep());
        if (is_debug_mode_) render_tick_.IncreaseFrameCounter();
      }

      if (!is_debug_mode_) continue;

      game_tick_.IncreaseElapsed();
      render_tick_.IncreaseElapsed();
      game_tick_.ShowFps("Game");
      render_tick_.ShowFps("RenderSprite");
    }
  }

  void AddScene(const std::string& name, entities::SceneCallbackFunction callback_function) {
    scene_manager_.AddScene(name, callback_function);
  }

  void SetActiveScene(const std::string& name) {
    scene_manager_.SetActiveScene(name);
  }

 private:
  SceneManager scene_manager_;

  std::unique_ptr<ui::Renderer> renderer_;
  std::unique_ptr<input::Input> input_;
  std::unique_ptr<physics::Physics> physics_;

  EngineTick game_tick_;
  EngineTick render_tick_;
  bool is_debug_mode_ = false;
  bool is_game_active_ = false;
};

Engine::Engine(EngineConfig engine_config) : impl_(new Impl(engine_config)) {}
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

}