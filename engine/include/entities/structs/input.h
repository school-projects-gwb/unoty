#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_INPUT_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_INPUT_H_

#include "vector"
#include "set"
#include "key.h"
#include "point.h"

namespace engine::entities {

class Input {
 public:
  static void SetLastKeyPress(const entities::Key& key) {
    last_key_press_ = key;
  }

  static const entities::Key& GetLastKeyPress() {
    return last_key_press_;
  }

  // Active keys

  static void AddActiveKey(const entities::Key& key) {
    active_keys_.insert(key);
  }

  static void RemoveActiveKey(const entities::Key& key) {
    active_keys_.erase(key);
  }

  static bool HasActiveKey(const entities::Key& key) {
    auto it = active_keys_.find(key);
    return it != active_keys_.end();
  }

  static const std::set<entities::Key>& GetActiveKeys() {
    return active_keys_;
  }

  // Pressed keys

  static void AddPressedKey(const entities::Key& key) {
    pressed_keys_.insert(key);
  }

  static bool HasPressedKey(const entities::Key& key) {
    auto it = pressed_keys_.find(key);
    return it != pressed_keys_.end();
  }

  static const std::set<entities::Key>& GetPressedKeys() {
    return pressed_keys_;
  }

  static void ClearPressedKeys() {
    pressed_keys_.clear();
  }

  // Released keys

  static void AddReleasedKey(const entities::Key& key) {
    released_keys_.insert(key);
  }

  static bool HasReleasedKey(const entities::Key& key) {
    auto it = released_keys_.find(key);
    return it != released_keys_.end();
  }

  static const std::set<entities::Key>& GetReleasedKeys() {
    return released_keys_;
  }

  static void ClearReleasedKeys() {
    released_keys_.clear();
  }

  // Mouse pressed

  static void SetIsMousePressed(bool is_pressed) {
    is_mouse_pressed_ = is_pressed;
  }

  static bool IsMousePressed() {
    return is_mouse_pressed_;
  }

  // Mouse released

  static void SetIsMouseReleased(bool is_released) {
    is_mouse_released_ = is_released;
  }

  static bool IsMouseReleased() {
    return is_mouse_released_;
  }

  // Mouse clicked

  static void SetIsMouseClicked(bool is_clicked) {
    is_mouse_clicked_ = is_clicked;
  }

  static bool IsMouseClicked() {
    return is_mouse_clicked_;
  }

  // Mouse moved

  static void SetIsMouseMoved(bool is_moved) {
    is_mouse_moved_ = is_moved;
  }

  static bool IsMouseMoved() {
    return is_mouse_moved_;
  }

  // Mouse pointer position

  static void SetMousePointerPosition(const entities::Point& position) {
    mouse_pointer_position_ = position;
  }

  /// @brief Gets mouse pointer position with world/camera position calculated in
  static const entities::Point& GetMousePointerPosition() {
    return mouse_pointer_position_;
  }

 private:
  static entities::Point mouse_pointer_position_;
  static bool is_mouse_clicked_;
  static bool is_mouse_pressed_;
  static bool is_mouse_released_;
  static bool is_mouse_moved_;

  static entities::Key last_key_press_;
  static std::set<entities::Key> active_keys_;
  static std::set<entities::Key> pressed_keys_;
  static std::set<entities::Key> released_keys_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_INPUT_H_
