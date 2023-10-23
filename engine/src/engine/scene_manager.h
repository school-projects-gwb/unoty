#ifndef ENGINE_SRC_ENGINE_SCENE_MANAGER_H_
#define ENGINE_SRC_ENGINE_SCENE_MANAGER_H_

#include <string>
#include <map>
#include <../include/entities/scene_callback_function.h>

namespace engine {

class SceneManager {
 public:
  SceneManager() = default;
  void AddScene(const std::string& scene_name, entities::SceneCallbackFunction callback_function);
  void SetActiveScene(const std::string& scene_name);
  std::shared_ptr<entities::Scene> GetActiveScene();
 private:
  std::shared_ptr<entities::Scene> active_scene_ = nullptr;
  std::map<std::string, entities::SceneCallbackFunction> scenes_ = {};
};

}

#endif //ENGINE_SRC_ENGINE_SCENE_MANAGER_H_
