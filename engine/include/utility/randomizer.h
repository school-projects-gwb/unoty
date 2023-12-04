#ifndef RANDOM_UTILS_LIBRARY_H
#define RANDOM_UTILS_LIBRARY_H

#include <random>
#include <vector>
#include <optional>

/// @brief Enables random number generation and some other randomization functionality
class Randomizer {
 public:
  static Randomizer& GetInstance() {
    static Randomizer instance;
    return instance;
  }

  Randomizer(const Randomizer&) = delete;
  Randomizer& operator=(const Randomizer&) = delete;

  int RandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random_engine_);
  }

  float RandomFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random_engine_);
  }

  bool RandomBool() {
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(random_engine_) == 1;
  }

  template <typename T>
  std::optional<T> RandomElement(const std::vector<T>& elements);

 private:
  Randomizer() : random_engine_(random_device_()) {}

  std::random_device random_device_;
  std::default_random_engine random_engine_;
};

template <typename T>
std::optional<T> Randomizer::RandomElement(const std::vector<T>& elements) {
  if (elements.empty())
    return std::nullopt;

  std::uniform_int_distribution<size_t> dist(0, elements.size() - 1);
  return elements[dist(random_engine_)];
}

#endif //RANDOM_UTILS_LIBRARY_H
