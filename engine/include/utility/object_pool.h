#ifndef ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_OBJECT_POOL_H_
#define ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_OBJECT_POOL_H_

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <memory>
#include "entities/game_object.h"

/// @brief Generic ObjectPool class for storing reusable objects
///
/// Provides flexibility by enabling custom callbacks for creation, releasing and acquiring objects.
/// @param T Type the Objects in the pool should have (can be polymorphic)
template <typename T>
class ObjectPool {
 public:
  using CreateCallback = std::function<std::shared_ptr<T>()>;
  using ReleaseCallback = std::function<void(std::shared_ptr<T>)>;
  using AcquireCallback = std::function<std::shared_ptr<T>(const std::vector<std::shared_ptr<T>>&)>;

  ObjectPool(AcquireCallback acquire_callback, ReleaseCallback release_callback)
      : acquire_callback_(acquire_callback), release_callback_(release_callback) {
  }

  /// @brief Pools objects and optionally adds them to current active Scene
  void PoolObjects(int amount, CreateCallback create_callback, bool add_to_scene) {
    for (auto i = 0; i < amount; i++) {
      auto object = create_callback();

      if (add_to_scene) engine::entities::GameObject::AddSceneObject(object);

      pooled_objects_.push_back(object);
    }
  }

  /// @brief Returns object (or nullptr if not found) based on registered AcquireCallback
  std::shared_ptr<T> Acquire() {
    if (pooled_objects_.empty()) {
      return nullptr;
    } else {
      return acquire_callback_(pooled_objects_);
    }
  }

  /// @brief Returns object to pool based on registered ReleaseCallback
  void Release(std::shared_ptr<T> obj) {
    if (!obj) return;

    release_callback_(obj);
  }

 private:
  std::vector<std::shared_ptr<T>> pooled_objects_;
  AcquireCallback acquire_callback_;
  ReleaseCallback release_callback_;
};

#endif //ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_OBJECT_POOL_H_
