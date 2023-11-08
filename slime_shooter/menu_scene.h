#ifndef SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_
#define SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_

#include <iostream>
#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "movement_script.h"
#include "entities/scene/scene_background.h"
#include "entities/animator.h"

using namespace engine::entities;

class MenuScene : engine::entities::Scene {
 public:
  static Scene* MenuSceneInit() {
    auto* scene = new MenuScene();

    return scene;
  }
};

#endif //SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_
