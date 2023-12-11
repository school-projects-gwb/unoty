#ifndef ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_PLAYER_TURRET_H_
#define ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_PLAYER_TURRET_H_

#include "artificial_intelligence.h"
namespace engine::entities {

class PlayerTurret : public ArtificialIntelligence {
  ~PlayerTurret();
  PlayerTurret();

  void TrackObject(std::shared_ptr<GameObject> object) override;
  void OnStart() override;
  void OnUpdate() override;
  void OnInput() override;
  void OnCollisionEnter(GameObject* &colliding_object) override;
  void OnCollisionExit(GameObject* &colliding_object) override;
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_PLAYER_TURRET_H_
