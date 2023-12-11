
#include <vector>
#include "entities/artificial_intelligence/player_turret.h"

namespace engine::entities {

class PlayerTurret::Impl {
 public:
  Impl() {}

  void TrackObject(std::shared_ptr<GameObject> object) {
    tracking_objects_.emplace_back(object);
  }

  void OnStart() {

  }

  void OnUpdate() {

  }

  void OnInput() {

  }

  void OnTriggerEnter2d(GameObject* &colliding_object) {

  }

  void OnTriggerExit2d(GameObject* &colliding_object) {

  }
 private:
  std::vector<std::shared_ptr<GameObject>> tracking_objects_;
};

PlayerTurret::PlayerTurret() : impl_(std::make_unique<Impl>()) {}
PlayerTurret::~PlayerTurret() = default;

void PlayerTurret::OnStart() {
  impl_->OnStart();
}

void PlayerTurret::OnUpdate() {
  impl_->OnUpdate();
}

void PlayerTurret::OnInput() {
  impl_->OnInput();
}

void PlayerTurret::OnCollisionEnter(GameObject* &colliding_object) {
  impl_->OnTriggerEnter2d(colliding_object);
}

void PlayerTurret::OnCollisionExit(GameObject* &colliding_object) {
  impl_->OnTriggerEnter2d(colliding_object);
}

void PlayerTurret::TrackObject(std::shared_ptr<GameObject> object) {

}

}