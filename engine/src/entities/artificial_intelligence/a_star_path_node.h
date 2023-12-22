
#ifndef ENGINE_SRC_ENTITIES_ARTIFICIAL_INTELLIGENCE_A_STAR_PATH_NODE_H
#define ENGINE_SRC_ENTITIES_ARTIFICIAL_INTELLIGENCE_A_STAR_PATH_NODE_H

#include "entities/structs/vector_2d.h"
#include "entities/transform.h"

namespace engine::entities {
struct PathNode {
  std::shared_ptr<Transform> position_;
  std::shared_ptr<Transform> parent_;

  double f_, g_;

  bool operator<(PathNode const &obj) const {
    return f_ < obj.f_;
  }
  bool operator>(PathNode const &obj) const {
    return f_ > obj.f_;
  }
};
}

namespace std {
template<>
struct less<engine::entities::PathNode>
{
  bool operator()(const engine::entities::PathNode& node1, const engine::entities::PathNode& node2) const
  {
    return node1.f_ < node2.f_;
  }
};
}

#endif //ENGINE_SRC_ENTITIES_ARTIFICIAL_INTELLIGENCE_A_STAR_PATH_NODE_H
