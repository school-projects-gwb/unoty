#ifndef ENGINE_SRC_INPUT_INPUT_H_
#define ENGINE_SRC_INPUT_INPUT_H_

#include "entities/structs/key.h"
#include "entities/structs/point.h"
#include <set>

namespace engine::input {

class Input {
 public:
  virtual ~Input() = default;
  virtual void ProcessInput() = 0;

  [[nodiscard]] virtual entities::Key GetLastKeyPress() const = 0;
  [[nodiscard]] virtual entities::Point GetLastMousePress() const = 0;
  [[nodiscard]] virtual bool GetIsMousePressed() const = 0;
  [[nodiscard]] virtual bool GetIsMouseReleased() const = 0;
  [[nodiscard]] virtual std::set<entities::Key> GetActiveKeys() const = 0;
};

}

#endif //ENGINE_SRC_INPUT_INPUT_H_
