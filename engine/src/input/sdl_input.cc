#include "sdl_input.h"

namespace engine::input {

SdlInput::SdlInput() {
  InitKeyMappings();
  if (SDL_Init(SDL_INIT_GAMECONTROLLER) == 0) {
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
      if (SDL_IsGameController(i)) game_pad_ = SDL_GameControllerOpen(i);
      entities::Input::SetIsGamepadPluggedIn(true);
    }
    SDL_GameControllerAddMappingsFromFile("resources/gamecontrollerdb.txt");
    InitializeGamepadMappings();
  } else
    std::cerr << "Failed to initialize SDL_GameController: " << SDL_GetError() << std::endl;
}

SdlInput::~SdlInput() {
  if (game_pad_ != nullptr) {
    SDL_GameControllerClose(game_pad_);
    game_pad_ = nullptr;
  }
}

void SdlInput::ProcessInput(const entities::Point &camera_position) {
  SDL_Event event;

  // Reset some input values
  entities::Input::ClearPressedKeys();
  entities::Input::ClearReleasedKeys();
  entities::Input::SetIsMouseClicked(false);
  entities::Input::SetIsMouseMoved(false);

  entities::Input::ClearPressedGamepadButtons();
  entities::Input::ClearReleasedGamepadButtons();

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:entities::Input::SetLastKeyPress(entities::Key::UnoWindowClosed);
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
          entities::Input::SetMousePointerPosition(GetMousePositionRelativeToCamera({event.button.x, event.button.y},
                                                                                    camera_position));
        }
        break;
      case SDL_MOUSEBUTTONUP:
        if (key_mappings_.find(event.button.button) != key_mappings_.end()) {
          if (key_mappings_[event.button.button] == entities::Key::UnoLeftMouseButton)
            entities::Input::SetIsMouseClicked(true);

          entities::Input::SetLastKeyPress(entities::Key::UnoNone);
          entities::Input::SetIsMousePressed(false);
          entities::Input::SetIsMouseReleased(true);
          entities::Input::SetMousePointerPosition(GetMousePositionRelativeToCamera({event.button.x, event.button.y},
                                                                                    camera_position));
        }
        break;
      case SDL_MOUSEMOTION:entities::Input::SetIsMouseMoved(true);
        entities::Input::SetMousePointerPosition(GetMousePositionRelativeToCamera({event.button.x, event.button.y},
                                                                                  camera_position));
        break;
      case SDL_CONTROLLERDEVICEADDED:if (!game_pad_) game_pad_ = SDL_GameControllerOpen(event.cdevice.which);
        entities::Input::SetIsGamepadPluggedIn(true);
        break;
      case SDL_CONTROLLERDEVICEREMOVED:
        if (game_pad_ && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(game_pad_))) {
          SDL_GameControllerClose(game_pad_);
          game_pad_ = nullptr;
          entities::Input::SetIsGamepadPluggedIn(false);
        }
        break;
      case SDL_CONTROLLERBUTTONDOWN:
        if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(game_pad_))) {
          if (gamepad_mappings_.find(static_cast<SDL_GameControllerButton>(event.cbutton.button))
              != gamepad_mappings_.end()) {
            entities::Input::SetLastButtonPress(gamepad_mappings_[static_cast<SDL_GameControllerButton>(event.cbutton.button)]);

            if (!entities::Input::HasActiveGamepadButton(entities::Input::GetLastButtonPress()))
              entities::Input::AddPressedGamepadButton(entities::Input::GetLastButtonPress());

            entities::Input::AddActiveGamepadButton(entities::Input::GetLastButtonPress());
          }
        }
        break;
      case SDL_CONTROLLERBUTTONUP:
        if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(game_pad_))) {
          if (gamepad_mappings_.find(static_cast<SDL_GameControllerButton>(event.cbutton.button))
              != gamepad_mappings_.end()) {
            entities::Input::SetLastButtonPress(entities::GamepadButton::None);
            auto btn = gamepad_mappings_[static_cast<SDL_GameControllerButton >(event.cbutton.button)];

            entities::Input::RemoveActiveGamepadButton(btn);
            entities::Input::AddReleasedGamepadButton(btn);
          }
        }
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
  key_mappings_[SDLK_PAGEDOWN] = entities::Key::UnoPageDown;
  key_mappings_[SDLK_PAGEUP] = entities::Key::UnoPageUp;
  key_mappings_[SDLK_HOME] = entities::Key::UnoHome;
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

void SdlInput::InitializeGamepadMappings() {
  // Letter buttons
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_Y] = entities::GamepadButton::Y;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_B] = entities::GamepadButton::B;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_A] = entities::GamepadButton::A;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_X] = entities::GamepadButton::X;

  // DPad
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_DPAD_UP] = entities::GamepadButton::Up;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = entities::GamepadButton::Right;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = entities::GamepadButton::Down;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = entities::GamepadButton::Left;

  // Middle buttons
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_START] = entities::GamepadButton::Start;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_GUIDE] = entities::GamepadButton::Guide;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_BACK] = entities::GamepadButton::Back;

  // Shoulder buttons
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] = entities::GamepadButton::LeftShoulder;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = entities::GamepadButton::RightShoulder;

  // Joysticks
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_LEFTSTICK] = entities::GamepadButton::LeftJoystick;
  gamepad_mappings_[SDL_CONTROLLER_BUTTON_RIGHTSTICK] = entities::GamepadButton::RightJoystick;
}

entities::Point SdlInput::GetMousePositionRelativeToCamera(const entities::Point &mouse_position,
                                                           const entities::Point &camera_position) {
  return {mouse_position.x + camera_position.x, mouse_position.y + camera_position.y};
}

}