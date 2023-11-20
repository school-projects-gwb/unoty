#include "entities/scene/scene_background.h"
#include "rendering/renderer.h"
#include <iostream>
#include <utility>
#include <map>

namespace engine::entities {

/// Custom comparison operator used in SceneBackground std::set structure
bool operator< ( Point a, Point b ) { return std::make_pair(a.x,a.y) < std::make_pair(b.x,b.y) ; }

class SceneBackground::Impl {
 public:
  explicit Impl(entities::Color background_color) : background_color_(background_color) {
  }

  Impl(std::string tile_map_image_path, entities::Point tile_map_col_row_amount, entities::Color background_color)
      : tile_map_col_row_amount_(tile_map_col_row_amount), tile_map_image_path_(std::move(tile_map_image_path)),
        background_color_(background_color), has_tile_map_(true) {
    InitTileMapTilePositions();
  }

  void RenderBackground(const std::unique_ptr<engine::ui::Renderer>& renderer) {
    TrySetBackgroundColor(renderer);
    if (!has_tile_map_) return;

    RenderTileMap(renderer);
  }

 private:
  const Point tile_map_tile_pixel_size_ = {32, 32};
  const Point tile_pixel_size_ = {128, 128};
  const Point tile_map_col_row_amount_ = {5, 5};
  const std::string tile_map_image_path_;
  const Color background_color_ = {0, 0, 0, 255};
  bool is_background_set_ = false;
  const bool has_tile_map_ = false;
  std::map<entities::Point, Point> tile_map_tile_positions_;

  void RenderTileMap(const std::unique_ptr<engine::ui::Renderer>& renderer) const {
    // Render corners and sides
    for (auto position : tile_map_tile_positions_) {
      structs::Rectangle render_position = GetRenderPosition(position.first.x, position.first.y);
      structs::Rectangle sheet_position = GetSheetPosition(position.second.x, position.second.y);
      renderer->GetSpriteRenderer()->RenderStaticSpriteFromSheet({tile_map_image_path_, {}, sheet_position,
                                                                  render_position}, {});
    }

    // Render fill
    for (auto y = 1; y < tile_map_col_row_amount_.y-1; y++)
      for (auto x = 1; x < tile_map_col_row_amount_.x-1; x++) {
        structs::Rectangle render_position = GetRenderPosition(x, y);
        structs::Rectangle sheet_position = GetSheetPosition(2, 0);
        renderer->GetSpriteRenderer()->RenderStaticSpriteFromSheet({tile_map_image_path_, {}, sheet_position,
                                                                    render_position}, {});
      }
  }

  [[nodiscard]] structs::Rectangle GetRenderPosition(int col, int row) const {
    return {col * tile_pixel_size_.x, row * tile_pixel_size_.y, tile_pixel_size_.x, tile_pixel_size_.y};
  }

  [[nodiscard]] structs::Rectangle GetSheetPosition(int col, int row) const {
    return {col, row, tile_map_tile_pixel_size_.x, tile_map_tile_pixel_size_.y};
  }

  void InitTileMapTilePositions() {
    SetTileMapCornerPositions();

    for (auto x = 1; x < tile_map_col_row_amount_.x - 1; x++) {
      tile_map_tile_positions_[{x, 0}] = {0, 2}; // Top side
      tile_map_tile_positions_[{x, tile_map_col_row_amount_.y - 1}] = {2, 2}; // Bottom side
    }

    for (auto y = 1; y < tile_map_col_row_amount_.y - 1; y++) {
      tile_map_tile_positions_[{0, y}] = {1, 2}; // Left side
      tile_map_tile_positions_[{tile_map_col_row_amount_.x - 1, y}] = {2, 1}; // Right side
    }
  }

  void SetTileMapCornerPositions() {
    // Corners; top left, top right, bottom left, bottom right respectively
    tile_map_tile_positions_[{0,0}] = {0,0};
    tile_map_tile_positions_[{tile_map_col_row_amount_.x-1, 0}] = {1, 0};
    tile_map_tile_positions_[{0, tile_map_col_row_amount_.y-1}] = {0, 1};
    tile_map_tile_positions_[{tile_map_col_row_amount_.x-1, tile_map_col_row_amount_.y-1}] = {1, 1};
  }

  void TrySetBackgroundColor(const std::unique_ptr<engine::ui::Renderer>& renderer) {
    if (is_background_set_) return;

    renderer->SetBackgroundRenderColor(background_color_);
    is_background_set_ = true;
  }
};

SceneBackground::SceneBackground(entities::Color background_color) : impl_(new Impl(background_color)) {}

SceneBackground::SceneBackground(const std::string& tile_map_image_path, entities::Point tile_map_col_row_amount,
                                 entities::Color background_color)
                                 : impl_(new Impl(tile_map_image_path, tile_map_col_row_amount,
                                                  background_color)) {}

SceneBackground::~SceneBackground() = default;

void SceneBackground::RenderBackground(const std::unique_ptr<engine::ui::Renderer>& renderer) {
  impl_->RenderBackground(renderer);
}

}

