#ifndef ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_CIRCLE_PATH_AROUND_OBJECT_AI_H
#define ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_CIRCLE_PATH_AROUND_OBJECT_AI_H

#include <utility>
#include <cmath>
#include "entities/component.h"
#include "entities/game_object.h"

namespace engine::entities {

class CircleAroundObjectAI : public Component {
 public:
  CircleAroundObjectAI();
  ~CircleAroundObjectAI();
  void Init(GameObject *p_object);
  [[nodiscard]] std::shared_ptr<Transform> GetNewPosition();
  void SetTarget(GameObject* target);

  float GetDistance();
  float GetSpeed();
  float GetAngle();
  float GetRotationSpeed();

  void SetDistance(float val);
  void SetSpeed(float val);
  void SetAngle(float val);
  void SetRotationSpeed(float val);

 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_CIRCLE_PATH_AROUND_OBJECT_AI_H
