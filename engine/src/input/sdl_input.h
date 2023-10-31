#ifndef ENGINE_SRC_INPUT_SDL_INPUT_H_
#define ENGINE_SRC_INPUT_SDL_INPUT_H_

#include <unordered_map>
#include "entities/structs/key.h"
#include "input.h"
#include <set>
#include "entities/structs/point.h"

namespace engine::input {

class SdlInput : public Input {
 public:
  SdlInput();
  void ProcessInput() override;
  [[nodiscard]] entities::Key GetLastKeyPress() const override;
  [[nodiscard]] entities::Point GetLastMousePress() const override;
  bool GetIsMousePressed() const override;
  bool GetIsMouseReleased() const override;
  [[nodiscard]] std::set<entities::Key> GetActiveKeys() const override;
 private:
  entities::Key last_key_press_ = entities::Key::None;
  entities::Point last_mouse_press_ = {};
  bool is_mouse_pressed_ = false;
  bool is_mouse_released_ = false;
  std::unordered_map<SDL_Keycode, entities::Key> key_mappings_;
  std::set<entities::Key> active_keys_;
};

}

#endif //ENGINE_SRC_INPUT_SDL_INPUT_H_
