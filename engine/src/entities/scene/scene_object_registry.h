#ifndef ENGINE_SRC_ENTITIES_SCENE_ENGINE_SRC_ENTITIES_SCENE_SCENE_OBJECT_REGISTRY_H_
#define ENGINE_SRC_ENTITIES_SCENE_ENGINE_SRC_ENTITIES_SCENE_SCENE_OBJECT_REGISTRY_H_

#include "vector"
#include "entities/game_object.h"
#include "entities/listeners/mouse_listener.h"
#include "entities/listeners/key_listener.h"

namespace engine::entities {

class SceneObjectRegistry {
 public:
  std::vector<std::shared_ptr<GameObject>> GetObjects();

  void AddObject(std::shared_ptr<GameObject> object);
  void RemoveObject(std::shared_ptr<GameObject> object);

  std::vector<std::shared_ptr<GameObject>> GetObjectsByTagName(const std::string &tag_name, bool search_recursive = false);
  std::shared_ptr<GameObject> GetObjectByName(const std::string &name, bool search_recursive = false);

  void AddListener(std::shared_ptr<Listener> listener);

  template<class T>
  std::vector<std::shared_ptr<T>> GetListenersByType();

 private:
  std::vector<std::shared_ptr<GameObject>> game_objects_;
  std::vector<std::shared_ptr<KeyListener>> key_listeners_;
  std::vector<std::shared_ptr<MouseListener>> mouse_listeners_;

  std::shared_ptr<GameObject> RecursiveNameSearch(const std::shared_ptr<GameObject>& object, const std::string& name);
  void RecursiveTagSearch(const std::shared_ptr<GameObject>& object, const std::string& tag_name,
                          std::vector<std::shared_ptr<GameObject>>& compatible_objects);
};

template<class T>
std::vector<std::shared_ptr<T>> SceneObjectRegistry::GetListenersByType() {
  if constexpr (std::is_same<T, KeyListener>::value) {
    return key_listeners_;
  } else if constexpr (std::is_same<T, MouseListener>::value) {
    return mouse_listeners_;
  }

  return {};
}

}

#endif //ENGINE_SRC_ENTITIES_SCENE_ENGINE_SRC_ENTITIES_SCENE_SCENE_OBJECT_REGISTRY_H_
