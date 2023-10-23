#include <iostream>
#include "engine/engine.h"
#include "entities/game_object.h"
#include "entities/colliders/box_collider.h"
#include "entities/colliders/circle_collider.h"
#include "test_scene.h"

using namespace engine::entities;

int main() {
  const int target_fps = 60;

  engine::EngineConfig engine_config;
  engine_config.render_tick_fps = 30;
  engine_config.game_tick_fps = 60;
  engine_config.is_debug_mode = true;

  engine::Engine engine(engine_config);

  auto box_collider = Component::Create<BoxCollider>();
  auto game_object = GameObject::Create();
  game_object->AddComponent(box_collider);
  auto has_circle_collider = game_object->GetComponentByType<CircleCollider>();
  auto has_box_collider = game_object->GetComponentByType<BoxCollider>();

  std::cout << has_circle_collider << "\n"; // nullptr
  std::cout << has_box_collider << "\n"; // valid position in memory

  // TestScene implements engine::entities::Scene
  engine.AddScene("test_scene", TestScene::CallbackTest);

  // Runs callback function of TestScene
  // This way you can create a scene and "initialise it's game objects in the Callback function
  // > which means a scene can be created and initialised later on
  engine.SetActiveScene("test_scene");

  std::cout << "\n";

  engine.Start();
}
