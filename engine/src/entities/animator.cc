#include <string>
#include <utility>
#include "entities/animator.h"
#include "entities/sprite.h"

namespace engine::entities {

class Animator::Impl {
 public:
  Impl(std::string sprite_path, int sprites_in_sheet, Point total_sprite_sheet_size) : sprite_(std::move(sprite_path)) {
    sprites_in_sheet_ = sprites_in_sheet;
    total_sprite_sheet_size_ = total_sprite_sheet_size;
  }

  void Play(bool is_looping) {
    is_playing_ = true;
    is_looping_ = is_looping;
  }

  void Stop() {
    is_playing_ = false;
  }

  void Update() {
    current_tick_++;
    if (current_tick_ == tick_rate_) {
      current_tick_ = 0;
      current_sprite_frame_ = 0;
    }

    // todo render current sprite frame
  }

 private:
  Sprite sprite_;
  int sprites_in_sheet_ = 0;
  int current_sprite_frame_ = 0;
  Point total_sprite_sheet_size_ = {};

  bool is_playing_ = false;
  bool is_looping_ = false;
  int tick_rate_ = 0;
  int current_tick_ = 0;
};

Animator::~Animator() = default;
Animator::Animator(std::string sprite_path, int sprites_in_sheet, Point total_sprite_sheet_size) :
impl_(new Impl(std::move(sprite_path), sprites_in_sheet, total_sprite_sheet_size)) {}

void Animator::Play(bool is_looping) {
  impl_->Play(is_looping);
}

void Animator::Stop() {
  impl_->Stop();
}

void Animator::Update() {
  impl_->Update();
}

}