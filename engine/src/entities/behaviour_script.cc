
#include "entities/behaviour_script.h"

namespace engine::entities {

class BehaviourScript::Impl {
 public:
  Impl() {}
};

BehaviourScript::BehaviourScript() : impl_(std::make_unique<Impl>()) {}
BehaviourScript::~BehaviourScript() = default;

void BehaviourScript::OnStart() {

}

void BehaviourScript::OnUpdate() {

}

void BehaviourScript::OnInput() {

}

void BehaviourScript::OnCollisionEnter(GameObject* &colliding_object) {
}

void BehaviourScript::OnCollisionExit(GameObject* &colliding_object) {
}

}