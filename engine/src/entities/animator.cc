#include <string>
#include <map>
#include <unordered_map>
#include <cmath>
#include "entities/animator.h"
#include "entities/sprite.h"
#include "utility/debug.h"

namespace engine::entities {

class Animator::Impl : public Component {
 public:
  Impl(std::string default_state_sprite_path, int sprites_in_sheet, Point sprite_pixel_size, Point sheet_col_row_count = {2, 2}) : default_state_sprite_(std::move(default_state_sprite_path)) {
    sprite_pixel_size_ = sprite_pixel_size;
    sheet_col_row_count_ = sheet_col_row_count;
    sprites_in_sheet_ = sprites_in_sheet;
    InitSpriteSheetFramePositionMap();
  }

  void Play(bool is_looping) {
    current_sprite_frame_ = 0;
    is_playing_ = true;
    is_looping_ = is_looping;
  }

  void Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<entities::Transform> transform) {
    if (!is_playing_) {
      default_state_sprite_.Render(renderer, transform);
      return;
    }

    entities::Point sprite_position_in_sheet_ = sprite_frame_to_sheet_position_map_[current_sprite_frame_];

    ui::RenderInfo sprite_render_info;
    sprite_render_info.sprite_path = current_active_sprite_sheet_;
    sprite_render_info.transform = transform;
    sprite_render_info.size = transform->GetSize();
    sprite_render_info.position_in_sheet = {sprite_position_in_sheet_.x, sprite_position_in_sheet_.y,
                                            sprite_pixel_size_.x, sprite_pixel_size_.y};

    if (has_color_overlay_) {
      renderer->RenderSpriteFromSheetWithColorOverlay(sprite_render_info,
                                                      {sprite_sheet_flip_, sprite_sheet_color_,});
    } else {
      renderer->RenderSpriteFromSheet(sprite_render_info, {sprite_sheet_flip_});
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
  Point sheet_col_row_count_ = {2, 2};

  bool is_playing_ = false;
  bool is_looping_ = false;
  int tick_rate_ = 10;
  int current_tick_ = 0;

  void InitSpriteSheetFramePositionMap() {
    // Maps positions for performance benefits; this way it only has to be calculated once
    int current_row = 0;
    int current_col = 0;

    for (auto sprite_number = 0; sprite_number < sprites_in_sheet_; ++sprite_number) {
      int row = current_row;
      int column = current_col;

      if (current_col == sheet_col_row_count_.x - 1) {
        current_row++;
        current_col = 0;
      } else {
        current_col++;
      }

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

Animator::Animator(std::string default_state_sprite_path, int sprites_in_sheet, Point sprite_pixel_size, Point sheet_row_col_count) :
impl_(new Impl(std::move(default_state_sprite_path), sprites_in_sheet, sprite_pixel_size, sheet_row_col_count)) {}

void Animator::Play(bool is_looping) {
  impl_->Play(is_looping);
}

void Animator::Render(const std::unique_ptr<ui::SpriteRenderer>& renderer, std::shared_ptr<entities::Transform> transform) {
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