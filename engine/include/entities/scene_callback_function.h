#ifndef ENGINE_INCLUDE_ENTITIES_SCENE_CALLBACK_FUNCTION_H_
#define ENGINE_INCLUDE_ENTITIES_SCENE_CALLBACK_FUNCTION_H_

#include "scene.h"
#include <functional>

namespace engine::entities {

/// @brief Callback function used when initialising Scene
typedef std::function<engine::entities::Scene*(void)> SceneCallbackFunction;

}

#endif //ENGINE_INCLUDE_ENTITIES_SCENE_CALLBACK_FUNCTION_H_
