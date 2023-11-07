#include <string>
#include <map>
#include <unordered_map>
#include <cmath>
#include "entities/animator.h"
#include "entities/sprite.h"
#include "helpers/debug.h"

namespace engine::entities {

class Animator::Impl : public Component {
 public:
  Impl(std::string default_state_sprite_path, int sprites_in_sheet, Point sprite_pixel_size) : default_state_sprite_(std::move(default_state_sprite_path)) {
    sprite_pixel_size_ = sprite_pixel_size;
    SetSpritesInSheet(sprites_in_sheet);
    InitSpriteSheetFramePositionMap();
  }

  void Play(bool is_looping) {
    current_sprite_frame_ = 0;
    is_playing_ = true;
    is_looping_ = is_looping;
  }

  void Render(const std::unique_ptr<engine::ui::Renderer>& renderer, std::shared_ptr<entities::Transform> transform) {
    if (!is_playing_) {
      default_state_sprite_.Render(renderer, transform);
      return;
    }

    entities::Point sprite_position_in_sheet_ = sprite_frame_to_sheet_position_map_[current_sprite_frame_];

    if (has_color_overlay_) {
      renderer->RenderSpriteFromSheetWithColorOverlay(current_active_sprite_sheet_, transform,
                                                      {sprite_position_in_sheet_.x, sprite_position_in_sheet_.y,
                                                       sprite_pixel_size_.x, sprite_pixel_size_.y}, sprite_sheet_color_,
                                                      sprite_sheet_flip_);
    } else {
      renderer->RenderSpriteFromSheet(current_active_sprite_sheet_, transform,
                                      {sprite_position_in_sheet_.x, sprite_position_in_sheet_.y,
                                       sprite_pixel_size_.x, sprite_pixel_size_.y}, sprite_sheet_flip_);
    }

    ProcessTickUpdate();
  }

  void Stop() {
    is_playing_ = false;
  }

  void SetSpriteSheetAtIndex(const std::string &sprite_path, int index) {
    sprite_sheets_[static_cast<int>(index)] = sprite_path;
  }

  void SetSpriteSheetAtIndex(const std::string &sprite_path, entities::SpriteAnimationState index) {
    sprite_sheets_[index] = sprite_path;
  }

  void SetCurrentAnimationSpriteSheet(entities::SpriteAnimationState index) {
    int integer_index = static_cast<int>(index);
    if (IsValidSpriteSheetIndex(integer_index))
      current_active_sprite_sheet_ = sprite_sheets_[integer_index];
  }

  void SetCurrentAnimationSpriteSheet(int index) {
    if (IsValidSpriteSheetIndex(index))
      current_active_sprite_sheet_ = sprite_sheets_[index];
  }

  void SetDefaultStateSprite(const std::string &sprite_path) {
    default_state_sprite_path_ = sprite_path;
  }

  void SetFlip(entities::SpriteFlip flip) {
    default_state_sprite_.SetFlip(flip);
    sprite_sheet_flip_ = flip;
  }

  void SetColor(entities::Color color) {
    if (color.r == 255 && color.g == 255 && color.b == 255) return;

    default_state_sprite_.SetColor(color);
    sprite_sheet_color_ = color;
    has_color_overlay_ = true;
  }

 private:
  Sprite default_state_sprite_;
  std::unordered_map<int, std::string> sprite_sheets_;
  std::string current_active_sprite_sheet_;
  std::string default_state_sprite_path_;
  entities::SpriteFlip sprite_sheet_flip_ = entities::SpriteFlip::FlipNone;
  entities::Color sprite_sheet_color_ {255, 255, 255};
  bool has_color_overlay_ = false;

  int sprites_in_sheet_ = 1;
  int current_sprite_frame_ = 0;
  std::unordered_map<int, entities::Point> sprite_frame_to_sheet_position_map_;
  Point sprite_pixel_size_ = {32, 32};

  bool is_playing_ = false;
  bool is_looping_ = false;
  int tick_rate_ = 10;
  int current_tick_ = 0;

  void SetSpritesInSheet(int amount) {
    double sqrt = std::sqrt(amount);
    if (sqrt - std::floor(sqrt) == 0) {
      sprites_in_sheet_ = amount;
      return;
    }

    helpers::Debug::Error("Animator: sprites_in_sheet does not translate to an equal amount of rows and columns.");
  }

  void InitSpriteSheetFramePositionMap() {
    // Maps positions for performance benefits; this way it only has to be calculated once
    int sprite_sheet_column_count = std::sqrt(sprites_in_sheet_);

    for (auto sprite_number = 0; sprite_number < sprites_in_sheet_; ++sprite_number) {
      int row = sprite_number / sprite_sheet_column_count;
      int column = sprite_number % sprite_sheet_column_count;
      sprite_frame_to_sheet_position_map_[sprite_number] = {column, row};
    }
  }

  bool IsValidSpriteSheetIndex(int index) {
    auto iterator = sprite_sheets_.find(index);
    if (iterator == sprite_sheets_.end())
      helpers::Debug::Error("Animator: No valid sprite sheet at index " + std::to_string(index) + ".");

    return iterator != sprite_sheets_.end();
  }

  void ProcessTickUpdate() {
    if (++current_tick_ < tick_rate_) return;

    current_tick_ = 0;
    if (++current_sprite_frame_ == sprites_in_sheet_) {
      current_sprite_frame_ = 0;
      if (!is_looping_) Stop();
    }
  }
};

Animator::~Animator() = default;

Animator::Animator(std::string default_state_sprite_path, int sprites_in_sheet, Point sprite_pixel_size) :
impl_(new Impl(std::move(default_state_sprite_path), sprites_in_sheet, sprite_pixel_size)) {}

void Animator::Play(bool is_looping) {
  impl_->Play(is_looping);
}

void Animator::Render(const std::unique_ptr<engine::ui::Renderer>& renderer, std::shared_ptr<entities::Transform> transform) {
  impl_->Render(renderer, transform);
}

void Animator::Stop() {
  impl_->Stop();
}

void Animator::SetSpriteSheetAtIndex(const std::string &sprite_path, int index) {
  impl_->SetSpriteSheetAtIndex(sprite_path, index);
}

void Animator::SetSpriteSheetAtIndex(const std::string &sprite_path, entities::SpriteAnimationState index) {
  impl_->SetSpriteSheetAtIndex(sprite_path, index);
}

void Animator::SetCurrentAnimationSpriteSheet(entities::SpriteAnimationState index) {
  impl_->SetCurrentAnimationSpriteSheet(index);
}

void Animator::SetCurrentAnimationSpriteSheet(int index) {
  impl_->SetCurrentAnimationSpriteSheet(index);
}

void Animator::SetDefaultStateSprite(const std::string &sprite_path) {
  impl_->SetDefaultStateSprite(sprite_path);
}

void Animator::SetFlip(entities::SpriteFlip flip) {
  impl_->SetFlip(flip);
}

void Animator::SetColor(entities::Color color) {
  impl_->SetColor(color);
}

}