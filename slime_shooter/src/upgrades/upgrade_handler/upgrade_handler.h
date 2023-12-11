#ifndef SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_H_
#define SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_H_

#include "entities/game_object.h"
#include "engine/engine_config.h"
#include "entities/ui/ui_object.h"
#include "common/definitions.h"
#include "upgrade_option.h"
#include "utility/randomizer.h"

using namespace engine::entities;

namespace slime_shooter {

class UpgradeHandler : public GameObject {
 public:
  UpgradeHandler() {
    int window_width = engine::EngineConfig::window_width;
    int window_height = engine::EngineConfig::window_height;
    Point option_size = {static_cast<int>(window_width * 0.3), static_cast<int>(window_height * 0.3)};
    int option_y_position = (window_height - option_size.y) / 2;

    auto background = GameObject::Create<UiObject>();
    background->SetBackgroundColor(Color{33, 62, 69, 200});
    background->GetTransform()->SetSize({window_width, window_height});

    auto level_up_text = GameObject::Create<UiText>();
    level_up_text->SetContent("LEVEL UP!");
    level_up_text->GetTransform()->Position = {window_width / 2 - 165, 75};
    level_up_text->SetFont(GameFont::Default, 40);
    level_up_text->SetColor(GameColor::Ui::TextGreen);

    auto choose_upgrade_text = GameObject::Create<UiText>();
    choose_upgrade_text->SetContent("CHOOSE YOUR UPGRADE");
    choose_upgrade_text->GetTransform()->Position = {window_width / 2 - 335, 150};
    choose_upgrade_text->SetFont(GameFont::Default, 36);
    choose_upgrade_text->SetColor(GameColor::Ui::TextPink);

    upgrade_applied_sound_ = Component::Create<AudioSource>("resources/audio/upgrade.wav");
    upgrade_applied_sound_->SetVolume(10);
    upgrade_applied_sound_->SetSpeed(75);
    AddComponent(upgrade_applied_sound_);

    AddChildObject(background);
    AddChildObject(level_up_text);
    AddChildObject(choose_upgrade_text);

    int option_padding = 30;
    auto option1 = GameObject::Create<UpgradeOption>(option_size, Vector2d{option_padding, option_y_position}, "1");
    auto option2 = GameObject::Create<UpgradeOption>(option_size, Vector2d{2*option_padding + option_size.x, option_y_position}, "2");
    auto option3 = GameObject::Create<UpgradeOption>(option_size, Vector2d{3*option_padding + option_size.x*2, option_y_position}, "3");

    options_.push_back(option1);
    options_.push_back(option2);
    options_.push_back(option3);

    AddChildObject(option1);
    AddChildObject(option2);
    AddChildObject(option3);

    SetName("upgrade_handler");
    SetIsActive(false);
  }

  void Show() {
    if (GetIsActive()) return;
    SetIsActive(true);

    if (!is_player_set_) SetPlayer();

    auto current_upgrade_type = player_statistics_->GetCurrentUpgradeType();
    auto applicable_upgrades = statistic_upgrades::GetStatisticUpgradesByType(current_upgrade_type);

    for (const auto& option : options_)
      option->SetContent(engine::utility::Randomizer::GetInstance().RandomElement(applicable_upgrades).value());

    engine::Engine::GetInstance().Pause([this]() { ProcessUpgrade(); });
  }

  void ProcessUpgrade() {
    switch (Input::GetLastKeyPress()) {
      case engine::entities::Key::Uno1:
        player_statistics_->ApplyUpgrade(options_.at(0)->GetUpgrade());
        break;
      case engine::entities::Key::Uno2:
        player_statistics_->ApplyUpgrade(options_.at(1)->GetUpgrade());
        break;
      case engine::entities::Key::Uno3:
        player_statistics_->ApplyUpgrade(options_.at(2)->GetUpgrade());
        break;
      default:
        return;
    }

    SetIsActive(false);
    engine::EngineConfig::is_paused = false;
    upgrade_applied_sound_->Play();
  }

 private:
  bool is_player_set_ = false;
  std::shared_ptr<GameObject> player_;
  std::shared_ptr<Statistics> player_statistics_;
  std::vector<std::shared_ptr<UpgradeOption>> options_;
  std::shared_ptr<AudioSource> upgrade_applied_sound_;

  void SetPlayer() {
    auto player = GameObject::GetSceneObjectByName("Player");
    player_statistics_ = player->GetComponentByType<Statistics>();
    is_player_set_ = true;
  }
};

}

#endif //SLIME_SHOOTER_SRC_UPGRADES_SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_H_
