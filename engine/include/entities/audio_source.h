#ifndef ENGINE_INCLUDE_ENTITIES_AUDIO_SOURCE_H_
#define ENGINE_INCLUDE_ENTITIES_AUDIO_SOURCE_H_

#include "component.h"

namespace engine::entities {

/// @brief Contains logic to play audio
class AudioSource : Component {
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_AUDIO_SOURCE_H_
