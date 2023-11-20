#ifndef ENGINE_SRC_ENGINE_SCENE_MANAGER_H_
#define ENGINE_SRC_ENGINE_SCENE_MANAGER_H_

#include <string>
#include <map>
#include "entities/scene/scene_callback_function.h"

namespace engine {

class SceneManager {
 public:
  static SceneManager& GetInstance();
  SceneManager(const SceneManager&) = delete;

  void AddScene(const std::string& scene_name, entities::SceneCallbackFunction callback_function);

  /// @brief Remove Scene if it exists, also sets current_scene_ to nullptr if this was the removed Scene.
  void RemoveScene(const std::string& scene_name);

  void SetActiveScene(const std::string& scene_name);
  void SetActiveScene(const std::string& scene_name, std::vector<std::shared_ptr<entities::GameObject>> objects_to_migrate);
  std::shared_ptr<entities::Scene> GetActiveScene();

  /// @brief Returns every single object from the current active Scene
  std::vector<std::shared_ptr<entities::GameObject>> GetAllObjects();

  /// @brief Get a vector (can be empty) of all objects in current active Scene that have the given tag name
  std::vector<std::shared_ptr<entities::GameObject>> GetObjectsByTagName(const std::string& tag_name,
                                                                         bool search_recursive = false);

  /// @brief Get singular object (can be nullptr) in current active Scene by name which acts as a unique identifier
  std::shared_ptr<entities::GameObject> GetObjectByName(const std::string& name, bool search_recursive = false);

  void AddObject(std::shared_ptr<entities::GameObject> object_to_add);

  /// @brief If given object shared pointer exists in Scene it will be removed
  void RemoveObject(std::shared_ptr<entities::GameObject> object_to_remove);
 private:
  SceneManager() = default;
  SceneManager& operator=(const SceneManager&) = delete;

  std::shared_ptr<entities::Scene> active_scene_ = nullptr;
  std::map<std::string, entities::SceneCallbackFunction> scenes_ = {};

  bool TryFindAndSetNewActiveScene(const std::string& scene_name);
};

}

#endif //ENGINE_SRC_ENGINE_SCENE_MANAGER_H_
