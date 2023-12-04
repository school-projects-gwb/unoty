#ifndef SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_UPGRADE_OPTION_H_
#define SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_UPGRADE_OPTION_H_

#include "entities/ui/ui_button.h"
#include "common/definitions.h"
#include "statistics/upgrades/statistic_upgrade.h"
#include "entities/ui/ui_text.h"
#include <iomanip>
#include <sstream>

using namespace engine::entities;

namespace slime_shooter {

class UpgradeOption : public GameObject {
 public:
  UpgradeOption(Point element_size, Vector2d element_position, std::string key_to_select) {
    auto background = GameObject::Create<UiObject>();
    background->SetBackgroundColor(GameColor::Ui::PrimaryButtonBackground);
    background->GetTransform()->Position = element_position;
    background->GetTransform()->SetSize(element_size);

    upgrade_header_text_ = GameObject::Create<UiText>();
    upgrade_header_text_->SetContent(".");
    upgrade_header_text_->GetTransform()->Position = {element_position.x + 25, element_position.y + 25};
    upgrade_header_text_->SetFont(GameFont::Default, 18);
    upgrade_header_text_->SetColor(GameColor::Ui::TextGreen);

    upgrade_amount_text_ = GameObject::Create<UiText>();
    upgrade_amount_text_->SetContent(".");
    upgrade_amount_text_->GetTransform()->Position = {element_position.x + 25, element_position.y + 120};
    upgrade_amount_text_->SetFont(GameFont::Default, 18);
    upgrade_amount_text_->SetColor(GameColor::Ui::TextRed);

    upgrade_footer_text_ = GameObject::Create<UiText>();
    upgrade_footer_text_->SetContent(".");
    upgrade_footer_text_->GetTransform()->Position = {element_position.x + 25, element_position.y + 165};
    upgrade_footer_text_->SetFont(GameFont::Default, 18);
    upgrade_footer_text_->SetColor(GameColor::Ui::TextWhite);

    auto upgrade_key_select_text = GameObject::Create<UiText>();
    upgrade_key_select_text->SetContent("<" + key_to_select + "> TO SELECT");
    upgrade_key_select_text->GetTransform()->Position = {element_position.x + 100, element_position.y + 225};
    upgrade_key_select_text->SetFont(GameFont::Default, 14);
    upgrade_key_select_text->SetColor(GameColor::Ui::TextPink);

    AddChildObject(background);
    AddChildObject(upgrade_header_text_);
    AddChildObject(upgrade_amount_text_);
    AddChildObject(upgrade_footer_text_);
    AddChildObject(upgrade_key_select_text);
  }

  void SetContent(statistic_upgrades::StatisticUpgrade upgrade) {
    upgrade_ = upgrade;
    upgrade_header_text_->SetContent(upgrade.name);

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << upgrade.value;
    upgrade_amount_text_->SetContent(stream.str());
    upgrade_footer_text_->SetContent(upgrade.label);
  }

  statistic_upgrades::StatisticUpgrade GetUpgrade() {
    return upgrade_;
  }

 private:
  std::shared_ptr<UiText> upgrade_header_text_;
  std::shared_ptr<UiText> upgrade_amount_text_;
  std::shared_ptr<UiText> upgrade_footer_text_;
  statistic_upgrades::StatisticUpgrade upgrade_;
};

}

#endif //SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_SLIME_SHOOTER_SRC_UPGRADES_UPGRADE_HANDLER_UPGRADE_OPTION_H_
