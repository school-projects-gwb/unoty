#ifndef ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_ARTIFICIAL_INTELLIGENCE_H_
#define ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_ARTIFICIAL_INTELLIGENCE_H_

#include "entities/behaviour_script.h"
namespace engine::entities {

class ArtificialIntelligence : public BehaviourScript {
 public:
  virtual void TrackObject(std::shared_ptr<GameObject> object) = 0;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_ARTIFICIAL_INTELLIGENCE_H_
