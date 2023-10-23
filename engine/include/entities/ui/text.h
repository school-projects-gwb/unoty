#ifndef ENGINE_INCLUDE_ENTITIES_UI_TEXT_H_
#define ENGINE_INCLUDE_ENTITIES_UI_TEXT_H_

#include "ui_object.h"

namespace engine::entities {

/// @brief UiObject - text
class Text : UiObject {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_UI_TEXT_H_
