#ifndef DEBUG_APP__GAME_SCENE_H_
#define DEBUG_APP__GAME_SCENE_H_

#include <iostream>
#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "movement_script.h"
#include "entities/scene/scene_background.h"

using namespace engine::entities;

class GameScene : engine::entities::Scene {
  public:
    static Scene* GameSceneInit() {
      auto* scene = new GameScene();

      // Create SceneBackground
      auto scene_background = std::make_unique<SceneBackground>(
          "resources/sprites/world/tilemap.png", Point{6,6},
          Color{0, 153, 133, 255});

      // Create GameObjects
      auto background_object = GameObject::Create();
      background_object->AddComponent(Component::Create<Sprite>("resources/sprites/world/fireplace.png"));
      background_object->GetTransform()->Position = {150, 80};
      background_object->GetTransform()->SetScale(2);

      auto player_object = GameObject::Create();

      player_object->AddComponent(Component::Create<Sprite>("resources/sprites/player/front_1.png"));
      player_object->AddComponent(Component::Create<MovementScript>());
      player_object->GetTransform()->Position = {250, 250};
      player_object->SetLayer(1);

      // Create Camera
      auto camera = std::make_unique<Camera>();
      camera->SetTrackingTransform(player_object->GetTransform());

      // Add GameObjects to Scene
      scene->AddObject(background_object);
      scene->AddObject(player_object);

      // Add Camera and Background to Scene
      scene->SetCamera(std::move(camera));
      scene->SetBackground(std::move(scene_background));

      return scene;
  }
};

#endif //DEBUG_APP__GAME_SCENE_H_
