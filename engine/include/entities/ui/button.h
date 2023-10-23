#ifndef ENGINE_INCLUDE_ENTITIES_UI_BUTTON_H_
#define ENGINE_INCLUDE_ENTITIES_UI_BUTTON_H_

#include "ui_object.h"

namespace engine::entities {

/// @brief UiObject - button
class Button : UiObject {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_UI_BUTTON_H_
