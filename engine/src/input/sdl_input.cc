#include <SDL_events.h>
#include <iostream>
#include "sdl_input.h"

namespace engine::input {

SdlInput::SdlInput() {
  key_mappings_[SDLK_UP] = entities::Key::Up;
  key_mappings_[SDLK_DOWN] = entities::Key::Down;
  key_mappings_[SDLK_LEFT] = entities::Key::Left;
  key_mappings_[SDLK_RIGHT] = entities::Key::Right;
  key_mappings_[SDL_BUTTON_LEFT] = entities::Key::LeftMouse;
  key_mappings_[SDL_BUTTON_RIGHT] = entities::Key::RightMouse;
}

void SdlInput::ProcessInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        is_window_closed_ = true;
        break;
      case SDL_KEYDOWN:
        if (key_mappings_.find(event.key.keysym.sym) != key_mappings_.end()) {
          last_key_press_ = key_mappings_[event.key.keysym.sym];
          active_keys_.insert(last_key_press_);
        }
        break;
      case SDL_KEYUP:
        last_key_press_ = entities::Key::None;
        if (key_mappings_.find(event.key.keysym.sym) != key_mappings_.end()) {
          active_keys_.erase(key_mappings_[event.key.keysym.sym]);
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (key_mappings_.find(event.button.button) != key_mappings_.end()) {
          last_key_press_ = key_mappings_[event.button.button];
          last_mouse_press_.x = event.button.x;
          last_mouse_press_.y = event.button.y;
          is_mouse_pressed_ = true;
          is_mouse_released_ = false;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        if (key_mappings_.find(event.button.button) != key_mappings_.end()) {
          last_key_press_ = entities::Key::None;
          is_mouse_pressed_ = false;
          is_mouse_released_ = true;
        }
        break;
      case SDL_MOUSEMOTION:
        // todo implement
        break;
    }
  }
}

entities::Key SdlInput::GetLastKeyPress() const {
  return last_key_press_;
}

entities::Point SdlInput::GetLastMousePress() const {
  return last_mouse_press_;
}

bool SdlInput::GetIsMousePressed() const {
  return is_mouse_pressed_;
}

bool SdlInput::GetIsMouseReleased() const {
  return is_mouse_released_;
}

std::set<entities::Key> SdlInput::GetActiveKeys() const {
  return active_keys_;
}

bool SdlInput::IsWindowClosed() {
  return is_window_closed_;
}

}