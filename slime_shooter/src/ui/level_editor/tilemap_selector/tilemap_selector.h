#ifndef SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_TILEMAP_SELECTOR_H_
#define SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_TILEMAP_SELECTOR_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_object.h"
#include "tilemap_next_button.h"
#include "tilemap_previous_button.h"

using namespace engine::entities;

namespace slime_shooter  {

class TilemapSelector : public UiObject {
 public:
  TilemapSelector(std::function<void(const std::string&)> set_tile_map_callback) {
    set_tile_map_callback_ = set_tile_map_callback;

    auto title_text = GameObject::Create<UiText>();
    title_text->GetTransform()->Position = {775, 50};
    title_text->GetTransform()->SetScale(0.75);
    title_text->SetColor(GameColor::DarkGreen::Shade1);
    title_text->SetContent("SELECT TILEMAP");
    title_text->SetFont(GameFont::Default, 16);
    AddChildObject(title_text);

    auto selected_tile_map_text = GameObject::Create<UiText>();
    selected_tile_map_text_ = GameObject::Cast<UiText>(selected_tile_map_text);

    selected_tile_map_text_->GetTransform()->Position = {815, 85};
    selected_tile_map_text_->GetTransform()->SetScale(0.75);
    selected_tile_map_text_->SetColor(GameColor::DarkGreen::Shade1);
    selected_tile_map_text_->SetFont(GameFont::Default, 16);
    AddChildObject(selected_tile_map_text_);

    tile_map_image_paths_.push_back({"Tilemap 1", "resources/sprites/world/tilemap.png"});
    tile_map_image_paths_.push_back({"Tilemap 2", "resources/sprites/world/tilemap_2.png"});

    if (LevelEditorConfig::IsNewLevel()) {
      auto first_tile_map_image_element = tile_map_image_paths_.begin();
      selected_tile_map_index_ = 0;
      selected_tile_map_ = {first_tile_map_image_element->first, first_tile_map_image_element->second};
      selected_tile_map_text_->SetContent(selected_tile_map_.first);
      set_tile_map_callback_(selected_tile_map_.second);
    } else {
      int index = 0;
      auto current_tile_map_path = LevelLoaderConfig::GetPropertyValue("tile_map_path");

      for (const auto& audio_path : tile_map_image_paths_) {
        if (audio_path.second == current_tile_map_path) {
          selected_tile_map_index_ = index;
          selected_tile_map_ = {audio_path.first, audio_path.second};
          selected_tile_map_text_->SetContent(audio_path.first);
        }

        index++;
      }
    }

    auto tilemap_next_button = GameObject::Create<TilemapNextButton>(ChangeTileMap);
    AddChildObject(tilemap_next_button);

    auto tilemap_previous_button = GameObject::Create<TilemapPreviousButton>(ChangeTileMap);
    AddChildObject(tilemap_previous_button);

    SetLayer(2);
    GetTransform()->SetSize({300, 100});
    GetTransform()->Position = {735, 25};
    SetBackgroundColor(GameColor::DarkGreen::Shade3);
  }

  static void ChangeTileMap(bool is_next) {
    int next_index = CalculateNextIndex(is_next);
    UpdateSelectedTileMap(next_index);

    set_tile_map_callback_(selected_tile_map_.second);
  }

 private:
  static inline std::function<void(const std::string&)> set_tile_map_callback_;
  static inline std::shared_ptr<UiText> selected_tile_map_text_;
  static inline int selected_tile_map_index_;
  static inline std::pair<std::string, std::string> selected_tile_map_;
  static inline std::vector<std::pair<std::string, std::string>> tile_map_image_paths_;

  static void UpdateSelectedTileMap(int new_index) {
    selected_tile_map_index_ = new_index;
    selected_tile_map_ = tile_map_image_paths_.at(new_index);
    selected_tile_map_text_->SetContent(selected_tile_map_.first);
  }

  static int CalculateNextIndex(bool is_next) {
    int next_index = is_next ? selected_tile_map_index_+1 : selected_tile_map_index_-1;
    if (next_index < 0) next_index = tile_map_image_paths_.size()-1;
    if (next_index > tile_map_image_paths_.size()-1) next_index = 0;

    return next_index;
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_TILEMAP_SELECTOR_TILEMAP_SELECTOR_H_
