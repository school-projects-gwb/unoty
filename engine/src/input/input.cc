#include "entities/structs/input.h"

namespace engine::entities {

Point Input::mouse_pointer_position_;
bool Input::is_mouse_clicked_ = false;
bool Input::is_mouse_pressed_ = false;
bool Input::is_mouse_released_ = false;
bool Input::is_mouse_moved_ = false;

Key Input::last_key_press_;
std::set<Key> Input::active_keys_;
std::set<Key> Input::pressed_keys_;
std::set<Key> Input::released_keys_;

}