#include "entities/listeners/gamepad_listener.h"

namespace engine::entities {
class GamepadListener::Impl : public Listener {
 public:
  Impl() = default;
};

GamepadListener::GamepadListener() : impl_(std::make_unique<Impl>()) {}
GamepadListener::~GamepadListener() = default;

void GamepadListener::OnButtonPressed() {}
void GamepadListener::OnButtonReleased() {}
void GamepadListener::OnLeftStickMoved() {}
void GamepadListener::OnRightStickMoved() {}

} // namespace engine::entities
