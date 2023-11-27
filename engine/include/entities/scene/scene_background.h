#ifndef ENGINE_INCLUDE_ENTITIES_ENGINE_INCLUDE_ENTITIES_SCENE_BACKGROUND_H_
#define ENGINE_INCLUDE_ENTITIES_ENGINE_INCLUDE_ENTITIES_SCENE_BACKGROUND_H_

#include <string>
#include "entities/structs/point.h"
#include "entities/structs/color.h"
#include "rendering/renderer.h"

namespace engine::entities {

/// @param tile_map_image_path Path to tile map; assume 32x32 pixels per tile, 9 tiles total.
/// @param tile_map_col_row_amount Amount of tile columns and rows that should be rendered
/// @param tile_map_tile_pixel_size The pixel size of each individual tile in the TileMap
/// @param tile_render_pixel_size The pixel size of each individual sprite in sheet that will be rendered to screen
/// @param background_color Color of background used outside of the tile map
struct TileMapConfig {
  std::string tile_map_image_path;
  entities::Point tile_map_col_row_amount;
  entities::Point tile_map_tile_pixel_size = {32, 32};
  entities::Point tile_render_pixel_size = {128, 128};
  entities::Color background_color;
};

/// @brief Contains Scene background TileMap and color information
class SceneBackground {
 public:
  /// @brief Creates SceneBackground without a tile map
  explicit SceneBackground(entities::Color background_color = {0,0,0, 255});

   /// @brief Initialises background with tile map and color
   ///
   /// Provided tile_map_image_path should contain 32x32 pixel tiles, 9 tiles in total in a 3x3 grid:
   /// Row 1: [x0y0] Top left tile;  [x1y0] Top right tile;  [x2y0] Fill tile
   /// Row 2: [x0y1] Bottom left tile;  [x1y1] Bottom right tile;  [x2y1] Right side tile
   /// Row 3: [x0y2] Top side tile;  [x1y2] Left side tile;  [x2y2] Bottom side tile
  SceneBackground(const TileMapConfig tile_map_config);

  ~SceneBackground();

  /// @brief Processes rendering of background color and (if set) tile map
  void RenderBackground(const std::unique_ptr<engine::ui::Renderer>& renderer);
 private:
  class Impl;
  const std::unique_ptr<Impl> impl_;
};

}

#endif //ENGINE_INCLUDE_ENTITIES_ENGINE_INCLUDE_ENTITIES_SCENE_BACKGROUND_H_
