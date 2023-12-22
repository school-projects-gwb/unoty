#include "engine/engine.h"
#include "scenes/game_scene.h"
#include "scenes/menu_scene.h"
#include "scenes/ai_demo_scene.h"
#include "scenes/level_editor_scene.h"
#include "config/level_loader_config.h"
#include "config/level_editor_config.h"
#include "config/game_config.h"
#include "scenes/stress_test_scene.h"
#include "scenes/platformer_scene.h"
#include "scenes/particle_scene.h"

using namespace engine::entities;

int main() {
  slime_shooter::statistic_upgrades::InitializeStatisticUpgradeMap();
  slime_shooter::GameConfig::ReloadConfig();
  slime_shooter::LevelLoaderConfig::ReloadLevelData();

  engine::EngineConfig::is_debug_mode = true;
  engine::EngineConfig::no_sound_mode = false;
  engine::EngineConfig::debug_font_path = slime_shooter::GameFont::Default;
  engine::EngineConfig::window_title = "Slime Shooter";
  engine::EngineConfig::gravity = {0.0f, 0.0f};

  engine::Engine::GetInstance().Init();

  engine::Engine::GetInstance().AddScene("game_scene", slime_shooter::GameScene::GameSceneInit);
  engine::Engine::GetInstance().AddScene("stress_test_scene", slime_shooter::StressTestScene::StressTestSceneInit);
  engine::Engine::GetInstance().AddScene("menu_scene", slime_shooter::MenuScene::MenuSceneInit);
  engine::Engine::GetInstance().AddScene("level_editor_scene", slime_shooter::LevelEditorScene::LevelEditorSceneInit);
  engine::Engine::GetInstance().AddScene("ai_demo_scene", slime_shooter::AiDemoScene::AiDemoSceneInit);
  engine::Engine::GetInstance().AddScene("platformer_scene",slime_shooter::showcase::PlatformerScene::PlatformerSceneInit);
  engine::Engine::GetInstance().AddScene("particles_scene",slime_shooter::showcase::ParticleScene::ParticleSceneInit);

  engine::Engine::GetInstance().SetActiveScene("menu_scene");

  engine::Engine::GetInstance().Start();

  engine::Engine::GetInstance().Shutdown();

  return 0;
}