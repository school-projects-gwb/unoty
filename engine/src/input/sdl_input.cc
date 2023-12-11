#include <SDL_events.h>
#include <iostream>
#include "sdl_input.h"

namespace engine::input {

SdlInput::SdlInput() {
  InitKeyMappings();
}

void SdlInput::ProcessInput(const entities::Point &camera_position) {
  SDL_Event event;

  // Reset some input values
  entities::Input::ClearPressedKeys();
  entities::Input::ClearReleasedKeys();
  entities::Input::SetIsMouseClicked(false);
  entities::Input::SetIsMouseMoved(false);

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        entities::Input::SetLastKeyPress(entities::Key::UnoWindowClosed);
        entities::Input::AddActiveKey(entities::Input::GetLastKeyPress());
        break;
      case SDL_KEYDOWN:
        if (key_mappings_.find(event.key.keysym.sym) != key_mappings_.end()) {
          entities::Input::SetLastKeyPress(key_mappings_[event.key.keysym.sym]);

          // Check if key has not yet been pressed, if not add it to pressed_keys
          if (!entities::Input::HasActiveKey(entities::Input::GetLastKeyPress()))
            entities::Input::AddPressedKey(entities::Input::GetLastKeyPress());

          entities::Input::AddActiveKey(entities::Input::GetLastKeyPress());
        }
        break;
      case SDL_KEYUP:
        if (key_mappings_.find(event.key.keysym.sym) != key_mappings_.end()) {
          entities::Input::SetLastKeyPress(entities::Key::UnoNone);
          auto key = key_mappings_[event.key.keysym.sym];

          entities::Input::RemoveActiveKey(key);
          entities::Input::AddReleasedKey(key);
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (key_mappings_.find(event.button.button) != key_mappings_.end()) {
          entities::Input::SetLastKeyPress(key_mappings_[event.button.button]);
          entities::Input::SetIsMousePressed(true);
          entities::Input::SetIsMouseReleased(false);
          entities::Input::SetMousePointerPosition(GetMousePositionRelativeToCamera({event.button.x, event.button.y}, camera_position));
        }
        break;
      case SDL_MOUSEBUTTONUP:
        if (key_mappings_.find(event.button.button) != key_mappings_.end()) {
          if (key_mappings_[event.button.button] == entities::Key::UnoLeftMouseButton)
            entities::Input::SetIsMouseClicked(true);

          entities::Input::SetLastKeyPress(entities::Key::UnoNone);
          entities::Input::SetIsMousePressed(false);
          entities::Input::SetIsMouseReleased(true);
          entities::Input::SetMousePointerPosition(GetMousePositionRelativeToCamera({event.button.x, event.button.y}, camera_position));
        }
        break;
      case SDL_MOUSEMOTION:
        entities::Input::SetIsMouseMoved(true);
        entities::Input::SetMousePointerPosition(GetMousePositionRelativeToCamera({event.button.x, event.button.y}, camera_position));
        break;
    }
  }

  entities::Point mouse_position{};
  SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
  entities::Input::SetMousePointerPosition(GetMousePositionRelativeToCamera(mouse_position, camera_position));
}

void SdlInput::InitKeyMappings() {
  // Arrows
  key_mappings_[SDLK_UP] = entities::Key::UnoUpArrow;
  key_mappings_[SDLK_DOWN] = entities::Key::UnoDownArrow;
  key_mappings_[SDLK_LEFT] = entities::Key::UnoLeftArrow;
  key_mappings_[SDLK_RIGHT] = entities::Key::UnoRightArrow;
  // Alphabet
  key_mappings_[SDLK_a] = entities::Key::UnoA;
  key_mappings_[SDLK_b] = entities::Key::UnoB;
  key_mappings_[SDLK_c] = entities::Key::UnoC;
  key_mappings_[SDLK_d] = entities::Key::UnoD;
  key_mappings_[SDLK_e] = entities::Key::UnoE;
  key_mappings_[SDLK_f] = entities::Key::UnoF;
  key_mappings_[SDLK_g] = entities::Key::UnoG;
  key_mappings_[SDLK_h] = entities::Key::UnoH;
  key_mappings_[SDLK_i] = entities::Key::UnoI;
  key_mappings_[SDLK_j] = entities::Key::UnoJ;
  key_mappings_[SDLK_k] = entities::Key::UnoK;
  key_mappings_[SDLK_l] = entities::Key::UnoL;
  key_mappings_[SDLK_m] = entities::Key::UnoM;
  key_mappings_[SDLK_n] = entities::Key::UnoN;
  key_mappings_[SDLK_o] = entities::Key::UnoO;
  key_mappings_[SDLK_p] = entities::Key::UnoP;
  key_mappings_[SDLK_q] = entities::Key::UnoQ;
  key_mappings_[SDLK_r] = entities::Key::UnoR;
  key_mappings_[SDLK_s] = entities::Key::UnoS;
  key_mappings_[SDLK_t] = entities::Key::UnoT;
  key_mappings_[SDLK_u] = entities::Key::UnoU;
  key_mappings_[SDLK_v] = entities::Key::UnoV;
  key_mappings_[SDLK_w] = entities::Key::UnoW;
  key_mappings_[SDLK_x] = entities::Key::UnoX;
  key_mappings_[SDLK_y] = entities::Key::UnoY;
  key_mappings_[SDLK_z] = entities::Key::UnoZ;
  // Digits
  key_mappings_[SDLK_0] = entities::Key::Uno0;
  key_mappings_[SDLK_1] = entities::Key::Uno1;
  key_mappings_[SDLK_2] = entities::Key::Uno2;
  key_mappings_[SDLK_3] = entities::Key::Uno3;
  key_mappings_[SDLK_4] = entities::Key::Uno4;
  key_mappings_[SDLK_5] = entities::Key::Uno5;
  key_mappings_[SDLK_6] = entities::Key::Uno6;
  key_mappings_[SDLK_7] = entities::Key::Uno7;
  key_mappings_[SDLK_8] = entities::Key::Uno8;
  key_mappings_[SDLK_9] = entities::Key::Uno9;
  // Special characters
  key_mappings_[SDLK_BACKSPACE] = entities::Key::UnoBackspace;
  key_mappings_[SDLK_TAB] = entities::Key::UnoTab;
  key_mappings_[SDLK_SPACE] = entities::Key::UnoSpace;
  key_mappings_[SDLK_LCTRL] = entities::Key::UnoLeftControl;
  key_mappings_[SDLK_LSHIFT] = entities::Key::UnoLeftShift;
  key_mappings_[SDLK_RCTRL] = entities::Key::UnoRightControl;
  key_mappings_[SDLK_RSHIFT] = entities::Key::UnoRightShift;
  // F-keys
  key_mappings_[SDLK_F1] = entities::Key::UnoF1;
  key_mappings_[SDLK_F2] = entities::Key::UnoF2;
  key_mappings_[SDLK_F3] = entities::Key::UnoF3;
  key_mappings_[SDLK_F4] = entities::Key::UnoF4;
  key_mappings_[SDLK_F5] = entities::Key::UnoF5;
  key_mappings_[SDLK_F6] = entities::Key::UnoF6;
  key_mappings_[SDLK_F7] = entities::Key::UnoF7;
  key_mappings_[SDLK_F8] = entities::Key::UnoF8;
  key_mappings_[SDLK_F9] = entities::Key::UnoF9;
  key_mappings_[SDLK_F10] = entities::Key::UnoF10;
  key_mappings_[SDLK_F11] = entities::Key::UnoF11;
  key_mappings_[SDLK_F12] = entities::Key::UnoF12;
  // Mouse buttons
  key_mappings_[SDL_BUTTON_LEFT] = entities::Key::UnoLeftMouseButton;
  key_mappings_[SDL_BUTTON_RIGHT] = entities::Key::UnoRightMouseButton;
}

entities::Point SdlInput::GetMousePositionRelativeToCamera(const entities::Point &mouse_position, const entities::Point &camera_position) {
  return {mouse_position.x + camera_position.x, mouse_position.y + camera_position.y};
}

}