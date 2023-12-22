#ifndef ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_FIND_PATH_TO_OBJECT_AI_H
#define ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_FIND_PATH_TO_OBJECT_AI_H

#include <utility>
#include <cmath>
#include "entities/component.h"
#include "entities/game_object.h"

namespace engine::entities {

class FindPathToObjectAI : public Component {
 public:
  FindPathToObjectAI();
  ~FindPathToObjectAI() override;
  void Init(std::shared_ptr<Transform> p_object);
  void SetTarget(std::shared_ptr<Transform> target);
  bool FindPath();
  [[nodiscard]] std::shared_ptr<Transform> GetNewPosition();

  float GetSpeed();
  void SetSpeed(float val);
  bool GetTargetReached();

  void AddInvalidTile(const std::string &tag);
  void ClearInvalidTiles();
  void RemoveInvalidTile(const std::string &tag);

  void AddWeightedTile(const std::string &tag, int weight);
  void ClearWeightedTiles();
  void RemoveWeightedTile(const std::string &tag);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_FIND_PATH_TO_OBJECT_AI_H
