#include "../include/entities/behaviour_script.h"

namespace engine::entities {

class BehaviourScript::Impl {
 public:
  Impl();
};

BehaviourScript::BehaviourScript() : impl_(new Impl()) {}
BehaviourScript::~BehaviourScript() = default;

void BehaviourScript::OnStart() {

}

void BehaviourScript::OnUpdate() {

}

void BehaviourScript::OnInput() {

}

void BehaviourScript::OnTriggerEnter2d(Collider &collider) {

}

void BehaviourScript::OnTriggerExit2d(Collider &collider) {

}

}