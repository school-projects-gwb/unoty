#ifndef SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_AUDIO_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_AUDIO_SELECTOR_AUDIO_SELECTOR_H_
#define SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_AUDIO_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_AUDIO_SELECTOR_AUDIO_SELECTOR_H_

#include "engine/engine_config.h"
#include "entities/ui/ui_object.h"
#include "audio_next_button.h"
#include "audio_previous_button.h"
#include "entities/ui/ui_text.h"

using namespace engine::entities;

namespace slime_shooter  {

class AudioSelector : public UiObject {
 public:
  AudioSelector(std::function<void(const std::string&)> set_audio_callback) {
    set_audio_callback_ = set_audio_callback;

    auto title_text = GameObject::Create<UiText>();
    title_text->GetTransform()->Position = {785, 200};
    title_text->GetTransform()->SetScale(0.75);
    title_text->SetColor(GameColor::DarkGreen::Shade1);
    title_text->SetContent("SELECT AUDIO");
    title_text->SetFont(GameFont::Default, 16);
    AddChildObject(title_text);

    auto selected_audio_text = GameObject::Create<UiText>();
    selected_audio_text_ = GameObject::Cast<UiText>(selected_audio_text);

    selected_audio_text_->GetTransform()->Position = {825, 235};
    selected_audio_text_->GetTransform()->SetScale(0.75);
    selected_audio_text_->SetColor(GameColor::DarkGreen::Shade1);
    selected_audio_text_->SetFont(GameFont::Default, 16);
    AddChildObject(selected_audio_text_);

    audio_file_paths_.push_back({"Track 1", "resources/audio/game.mp3"});
    audio_file_paths_.push_back({"Track 2", "resources/audio/game_2.mp3"});

    if (LevelEditorConfig::IsNewLevel()) {
      auto first_audio_element = audio_file_paths_.begin();
      selected_audio_index_ = 0;
      selected_audio_ = {first_audio_element->first, first_audio_element->second};
      selected_audio_text_->SetContent(selected_audio_.first);
      set_audio_callback_(selected_audio_.second);
    } else {
      int index = 0;
      auto current_music_path = LevelLoaderConfig::GetPropertyValue("background_music_path");
      for (const auto& audio_path : audio_file_paths_) {
        if (audio_path.second == current_music_path) {
          selected_audio_index_ = index;
          selected_audio_ = {audio_path.first, audio_path.second};
          selected_audio_text_->SetContent(audio_path.first);
        }

        index++;
      }
    }

    auto audio_next_button = GameObject::Create<AudioNextButton>(ChangeAudio);
    AddChildObject(audio_next_button);

    auto audio_previous_button = GameObject::Create<AudioPreviousButton>(ChangeAudio);
    AddChildObject(audio_previous_button);

    SetLayer(2);
    GetTransform()->SetSize({300, 100});
    GetTransform()->Position = {735, 175};
    SetBackgroundColor(GameColor::DarkGreen::Shade3);
  }

  static void ChangeAudio(bool is_next) {
    int next_index = CalculateNextIndex(is_next);
    UpdateSelectedAudio(next_index);

    set_audio_callback_(selected_audio_.second);
  }

 private:
  static inline std::function<void(const std::string&)> set_audio_callback_;
  static inline std::shared_ptr<UiText> selected_audio_text_;
  static inline int selected_audio_index_;
  static inline std::pair<std::string, std::string> selected_audio_;
  static inline std::vector<std::pair<std::string, std::string>> audio_file_paths_;

  static void UpdateSelectedAudio(int new_index) {
    selected_audio_index_ = new_index;
    selected_audio_ = audio_file_paths_.at(new_index);
    selected_audio_text_->SetContent(selected_audio_.first);
  }

  static int CalculateNextIndex(bool is_next) {
    int next_index = is_next ? selected_audio_index_+1 : selected_audio_index_-1;
    if (next_index < 0) next_index = audio_file_paths_.size()-1;
    if (next_index > (int)audio_file_paths_.size()-1) next_index = 0;

    return next_index;
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_AUDIO_SELECTOR_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_AUDIO_SELECTOR_AUDIO_SELECTOR_H_
