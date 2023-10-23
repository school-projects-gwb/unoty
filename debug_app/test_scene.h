#ifndef DEBUG_APP__TEST_SCENE_H_
#define DEBUG_APP__TEST_SCENE_H_

#include <iostream>
#include "entities/scene.h"
class TestScene : engine::entities::Scene {
 public:
   static Scene* CallbackTest() {
     std::cout << "I'm a scene callback function";
     TestScene* scene = new TestScene();
     return scene;
  }
};

#endif //DEBUG_APP__TEST_SCENE_H_
