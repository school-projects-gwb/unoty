#include "entities/listeners/mouse_listener.h"

namespace engine::entities {

class MouseListener::Impl : public Listener {
 public:
  Impl() {}
};

MouseListener::MouseListener() : impl_(std::make_unique<Impl>()) {}
MouseListener::~MouseListener() = default;

void MouseListener::OnMouseClicked() {}

void MouseListener::OnMouseMoved() {}

void MouseListener::OnMousePressed() {}

void MouseListener::OnMouseReleased() {}

}