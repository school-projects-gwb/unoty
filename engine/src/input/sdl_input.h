#ifndef ENGINE_SRC_INPUT_SDL_INPUT_H_
#define ENGINE_SRC_INPUT_SDL_INPUT_H_

#include <unordered_map>
#include "entities/structs/key.h"
#include "input.h"
#include <set>
#include <SDL_keycode.h>
#include "entities/structs/point.h"
#include "entities/structs/input.h"

namespace engine::input {

class SdlInput : public Input {
 public:
  SdlInput();
  void ProcessInput(const entities::Point &camera_position) override;
 private:
  std::unordered_map<SDL_Keycode, entities::Key> key_mappings_;
  entities::Input input_;

  void InitKeyMappings();
  entities::Point GetMousePositionRelativeToCamera(const entities::Point &mouse_position, const entities::Point &camera_position);
};

}

#endif //ENGINE_SRC_INPUT_SDL_INPUT_H_
