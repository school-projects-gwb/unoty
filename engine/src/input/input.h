#ifndef ENGINE_SRC_INPUT_INPUT_H_
#define ENGINE_SRC_INPUT_INPUT_H_

#include "entities/structs/key.h"
#include "entities/structs/point.h"
#include "entities/structs/input.h"
#include <set>

namespace engine::input {

class Input {
 public:
  virtual ~Input() = default;
  virtual void ProcessInput() = 0;
};

}

#endif //ENGINE_SRC_INPUT_INPUT_H_
