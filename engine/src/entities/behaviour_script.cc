
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

void BehaviourScript::OnInput(const Key &key) {

}

void BehaviourScript::OnTriggerEnter2d(Collider &collider) {

}

void BehaviourScript::OnTriggerExit2d(Collider &collider) {

}

}