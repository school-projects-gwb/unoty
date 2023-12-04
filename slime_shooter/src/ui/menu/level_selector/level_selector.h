#ifndef SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_H_
#define SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_H_

#include <utility>

#include "engine/engine_config.h"
#include "entities/ui/ui_object.h"
#include "level_next_button.h"
#include "level_previous_button.h"
#include "entities/ui/ui_text.h"
#include "config/game_config.h"
#include "config/level_loader_config.h"

using namespace engine::entities;

namespace slime_shooter  {

class LevelSelector : public UiObject {
 public:
  explicit LevelSelector(std::function<void(const std::pair<std::string, std::string>&)> set_level_callback) {
    level_paths_.clear();
    set_level_callback_ = std::move(set_level_callback);

    auto selected_tile_map_text = GameObject::Create<UiText>();
    selected_tile_map_text->SetContent(".");
    selected_level_text_ = GameObject::Cast<UiText>(selected_tile_map_text);

    selected_level_text_->GetTransform()->Position = {540, 208};
    selected_level_text_->GetTransform()->SetScale(0.75);
    selected_level_text_->SetColor(GameColor::DarkGreen::Shade1);
    selected_level_text_->SetFont(GameFont::Default, 16);

    AddChildObject(selected_level_text_);

    int index = 0;
    for (const auto& available_level : LevelLoaderConfig::GetAvailableLevels()) {
      level_paths_.emplace_back(available_level.first, available_level.second);

      if (available_level.second == GameConfig::GetPropertyValue("active_level_path")) {
        selected_level_index_ = index;
        selected_level_ = {available_level.first, available_level.second};
        selected_level_text_->SetContent(available_level.first);
      }

      index++;
    }

    auto level_next_button = GameObject::Create<LevelNextButton>(ChangeLevel);
    AddChildObject(level_next_button);

    auto level_previous_button = GameObject::Create<LevelPreviousButton>(ChangeLevel);
    AddChildObject(level_previous_button);

    SetLayer(2);
    GetTransform()->SetSize({300, 60});
    GetTransform()->Position = {450, 185};
    SetBackgroundColor(GameColor::DarkGreen::Shade3);
  }

  static void ChangeLevel(bool is_next) {
    int next_index = CalculateNextIndex(is_next);
    UpdateSelectedLevel(next_index);
  }

 private:
  static inline std::function<void(const std::pair<std::string, std::string>&)> set_level_callback_ = nullptr;
  static inline std::shared_ptr<UiText> selected_level_text_ = nullptr;
  static inline int selected_level_index_;
  static inline std::pair<std::string, std::string> selected_level_;
  static inline std::vector<std::pair<std::string, std::string>> level_paths_;

  static void UpdateSelectedLevel(int new_index) {
    selected_level_index_ = new_index;
    selected_level_ = level_paths_.at(new_index);
    selected_level_text_->SetContent(selected_level_.first);

    set_level_callback_(selected_level_);
  }

  static int CalculateNextIndex(bool is_next) {
    int next_index = is_next ? selected_level_index_+1 : selected_level_index_-1;
    if (next_index < 0) next_index = level_paths_.size()-1;
    if (next_index > (int)level_paths_.size()-1) next_index = 0;

    return next_index;
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_MENU_SLIME_SHOOTER_SRC_UI_MENU_LEVEL_SELECTOR_H_
