#ifndef ENGINE_SRC_INPUT_SDL_INPUT_H_
#define ENGINE_SRC_INPUT_SDL_INPUT_H_

#include "input.h"

#include <set>
#include <unordered_map>
#include <iostream>

#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <SDL_keycode.h>
#include <SDL_events.h>

#include "entities/structs/key.h"
#include "entities/structs/point.h"
#include "entities/structs/input.h"

namespace engine::input {

class SdlInput : public Input {
 public:
  SdlInput();
  ~SdlInput() override;

  void ProcessInput(const entities::Point &camera_position) override;
 private:
  SDL_GameController *game_pad_ = nullptr;

  std::unordered_map<SDL_GameControllerButton, entities::GamepadButton> gamepad_mappings_;
  std::unordered_map<SDL_Keycode, entities::Key> key_mappings_;

  entities::Input input_;

  /// @brief Binds the SDL_Keycodes to their UNOTY counterparts.
  void InitKeyMappings();

  /// @brief Binds the SDL_GameController binds to their UNOTY counterparts.
  void InitializeGamepadMappings();

  static entities::Point GetMousePositionRelativeToCamera(const entities::Point &mouse_position, const entities::Point &camera_position);
};

}

#endif //ENGINE_SRC_INPUT_SDL_INPUT_H_
