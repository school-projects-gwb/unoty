#include "entities/listeners/key_listener.h"

namespace engine::entities {

class KeyListener::Impl : public Listener {
 public:
  Impl() {}
};

KeyListener::KeyListener() : impl_(std::make_unique<Impl>()) {}
KeyListener::~KeyListener() = default;

void KeyListener::OnKeyPressed() {}

void KeyListener::OnKeyReleased() {}
}