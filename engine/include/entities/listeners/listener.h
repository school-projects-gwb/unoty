#ifndef ENGINE_INCLUDE_ENTITIES_LISTENERS_ENGINE_INCLUDE_ENTITIES_LISTENERS_LISTENER_H_
#define ENGINE_INCLUDE_ENTITIES_LISTENERS_ENGINE_INCLUDE_ENTITIES_LISTENERS_LISTENER_H_

namespace engine::entities {

/// @brief purely virtual without any functions used for polymorphism
class Listener {
 public:
  virtual ~Listener() = default;
};

}


#endif //ENGINE_INCLUDE_ENTITIES_LISTENERS_ENGINE_INCLUDE_ENTITIES_LISTENERS_LISTENER_H_
