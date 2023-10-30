#ifndef DEBUG_APP__TEST_SCENE_H_
#define DEBUG_APP__TEST_SCENE_H_

#include <iostream>
#include "entities/scene.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "movement_script.h"

using namespace engine::entities;

class TestScene : engine::entities::Scene {
  public:
    static Scene* CallbackTest() {
     auto* scene = new TestScene();

     auto camera = std::make_unique<Camera>();

     auto game_object = GameObject::Create();
     auto sprite = Component::Create<Sprite>("resources/sprites/player/front_1.png");
     game_object->AddComponent(sprite);
     game_object->AddComponent(Component::Create<MovementScript>());

     scene->AddObject(game_object);
     scene->SetCamera(std::move(camera));

     return scene;
  }
};

#endif //DEBUG_APP__TEST_SCENE_H_
