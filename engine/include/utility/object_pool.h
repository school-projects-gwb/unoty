#ifndef ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_OBJECT_POOL_H_
#define ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_OBJECT_POOL_H_

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <memory>
#include "entities/game_object.h"

namespace engine::utility {

/// @brief Generic ObjectPool class for storing reusable objects
///
/// Provides flexibility by enabling custom callbacks for creation, releasing and acquiring objects.
/// @param T Type the Objects in the pool should have (can be polymorphic)
template <typename T>
class ObjectPool {
 public:
  using CreateCallback = std::function<std::shared_ptr<T>()>;
  using ReleaseCallback = std::function<void(std::shared_ptr<T>)>;
  using AcquireCallback = std::function<std::shared_ptr<T>(const std::vector<std::weak_ptr<T>>&)>;
  using PoolCallback = std::function<void()>;

  ObjectPool(AcquireCallback acquire_callback, ReleaseCallback release_callback, PoolCallback pool_callback)
      : acquire_callback_(acquire_callback), release_callback_(release_callback), pool_callback_(pool_callback) {
    pool_callback_();
  }

  ~ObjectPool() {
    for (auto& wp : pooled_objects_) {
      if (auto locked = wp.lock()) {
        //release_callback_(locked);
        engine::entities::GameObject::RemoveSceneObject(locked);
      }
    }

    pooled_objects_.clear();
  }

  /// @brief Pools objects and optionally adds them to current active Scene
  void PoolObjects(int amount, CreateCallback create_callback) {
    for (auto i = 0; i < amount; i++) {
      auto object = create_callback();

      engine::entities::GameObject::AddSceneObject(object);

      pooled_objects_.push_back(object);
    }
  }

  /// @brief Returns object (or nullptr if not found) based on registered AcquireCallback
  ///
  /// When none of the pooled weak pointers are pointing to existing object, objects get pooled again
  /// and old, invalid objects get cleared
  std::shared_ptr<T> Acquire() {
    auto it = std::remove_if(pooled_objects_.begin(), pooled_objects_.end(),
                             [](const std::weak_ptr<T>& wp) { return wp.expired(); });

    pooled_objects_.erase(it, pooled_objects_.end());

    if (pooled_objects_.empty())
      pool_callback_();

    return acquire_callback_(pooled_objects_);
  }

  /// @brief Returns object to pool based on registered ReleaseCallback
  void Release(std::shared_ptr<T> obj) {
    if (!obj) return;

    release_callback_(obj);
  }

 private:
  std::vector<std::weak_ptr<T>> pooled_objects_;
  AcquireCallback acquire_callback_;
  ReleaseCallback release_callback_;
  PoolCallback pool_callback_;
};

}

#endif //ENGINE_INCLUDE_UTILITY_ENGINE_INCLUDE_UTILITY_OBJECT_POOL_H_
