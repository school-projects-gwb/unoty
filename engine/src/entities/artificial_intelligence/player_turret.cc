
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

  void OnInput(const Key& key) {

  }

  void OnTriggerEnter2d(Collider& collider) {

  }

  void OnTriggerExit2d(Collider& collider) {

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

void PlayerTurret::OnInput(const Key& key) {
  impl_->OnInput(key);
}

void PlayerTurret::OnTriggerEnter2d(Collider& collider) {
  impl_->OnTriggerEnter2d(collider);
}

void PlayerTurret::OnTriggerExit2d(Collider& collider) {
  impl_->OnTriggerEnter2d(collider);
}

}