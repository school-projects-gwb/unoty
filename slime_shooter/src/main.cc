#include "engine/engine.h"
#include "scenes/game_scene.h"
#include "scenes/menu_scene.h"

using namespace engine::entities;

int main() {
  engine::EngineConfig::game_tick_fps = 60;
  engine::EngineConfig::is_debug_mode = true;
  engine::EngineConfig::debug_font_path = slime_shooter::GameFont::Default;
  engine::EngineConfig::window_title = "Slime Shooter";

  engine::Engine::GetInstance().Init();

  // TestScene implements engine::entities::Scene
  engine::Engine::GetInstance().AddScene("game_scene", slime_shooter::GameScene::GameSceneInit);
  engine::Engine::GetInstance().AddScene("menu_scene", slime_shooter::MenuScene::MenuSceneInit);

  // Runs callback function of TestScene
  // This way you can create a scene and "initialise it's game objects in the Callback function
  // > which means a scene can be created and initialised later on
  engine::Engine::GetInstance().SetActiveScene("menu_scene");

  engine::Engine::GetInstance().Start();

  // Makes sure all memory is freed
  engine::Engine::GetInstance().Shutdown();

  return 0;
}
