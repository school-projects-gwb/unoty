#ifndef ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_DEBUG_INFO_H_
#define ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_DEBUG_INFO_H_

#include "vector"
#include "string"
#include "vector_2d.h"

namespace engine::entities {
  struct DebugInfo {
    std::string font_path;
    int most_recent_fps;
    std::vector<std::pair<entities::Vector2d, entities::Vector2d>> debug_rectangles;
  };
}

#endif //ENGINE_INCLUDE_ENTITIES_STRUCTS_ENGINE_INCLUDE_ENTITIES_STRUCTS_DEBUG_INFO_H_
