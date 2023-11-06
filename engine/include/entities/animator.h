#ifndef ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_
#define ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_

#include "component.h"

namespace engine::entities {

class Animator : Component {
 public:
  Animator(std::string sprite_path, int sprites_in_sheet, Point total_sprite_sheet_size);
  ~Animator();

  void Play(bool is_looping);
  void Stop();
  void Update();
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ANIMATOR_H_
