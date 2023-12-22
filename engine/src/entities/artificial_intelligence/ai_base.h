
#ifndef ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_AI_BASE_H
#define ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_AI_BASE_H

#include <utility>

#include "entities/component.h"
#include "entities/game_object.h"

namespace engine::entities {

class AIBase : public Component {
 public:
  void Init(std::shared_ptr<Transform> ptr) {
    this_ = std::move(ptr);
    position_ = std::make_shared<Transform>();
    *position_ = *this_;
  }

  [[nodiscard]] virtual std::shared_ptr<Transform> GetNewPosition() = 0;
 protected:
  std::shared_ptr<Transform> this_;
  std::shared_ptr<Transform> position_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ARTIFICIAL_INTELLIGENCE_AI_BASE_H
