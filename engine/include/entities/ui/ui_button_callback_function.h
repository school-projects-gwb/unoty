#ifndef ENGINE_INCLUDE_ENTITIES_UI_ENGINE_INCLUDE_ENTITIES_UI_UI_BUTTON_CALLBACK_FUNCTION_H_
#define ENGINE_INCLUDE_ENTITIES_UI_ENGINE_INCLUDE_ENTITIES_UI_UI_BUTTON_CALLBACK_FUNCTION_H_

#include <functional>

namespace engine::entities {

/// @brief Callback function used when clicking on UiButton
typedef std::function<void()> UiButtonCallbackFunction;

}

#endif //ENGINE_INCLUDE_ENTITIES_UI_ENGINE_INCLUDE_ENTITIES_UI_UI_BUTTON_CALLBACK_FUNCTION_H_
