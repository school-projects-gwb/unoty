#include <iostream>
#include "engine/engine.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/colliders/box_collider.h"
#include "entities/colliders/circle_collider.h"
#include "game_scene.h"

using namespace engine::entities;

int main() {
  engine::EngineConfig engine_config;
  engine_config.render_tick_fps = 30;
  engine_config.game_tick_fps = 30;
  engine_config.is_debug_mode = false;
  engine_config.window_title = "Slime Shooter";

  engine::Engine engine(engine_config);

  // TestScene implements engine::entities::Scene
  engine.AddScene("test_scene", GameScene::GameSceneInit);

  // Runs callback function of TestScene
  // This way you can create a scene and "initialise it's game objects in the Callback function
  // > which means a scene can be created and initialised later on
  engine.SetActiveScene("test_scene");

  engine.Start();
}
