#ifndef SLIME_SHOOTER_SRC_UI_HUD_GOD_MODE_INDICATOR_GOD_MODE_INDICATOR_LOGIC_H
#define SLIME_SHOOTER_SRC_UI_HUD_GOD_MODE_INDICATOR_GOD_MODE_INDICATOR_LOGIC_H

#include "entities/behaviour_script.h"
#include "engine/engine_config.h"
#include "entities/ui/ui_text.h"

using namespace engine::entities;

namespace slime_shooter {

class GodModeIndicatorLogic : public BehaviourScript {
 public:
  void OnStart() override {
    auto godmode_indicator_gameobject = GameObject::GetSceneObjectByName("god_mode_indicator_text", true);
    godmode_indicator_text = GameObject::Cast<UiText>(godmode_indicator_gameobject);
  }

  void OnUpdate() override {
    godmode_indicator_text->SetContent(engine::EngineConfig::player_god_mode ? "Godmode enabled" : " ");
  }

 private:
  std::shared_ptr<UiText> godmode_indicator_text;
};

}


#endif //SLIME_SHOOTER_SRC_UI_HUD_GOD_MODE_INDICATOR_GOD_MODE_INDICATOR_LOGIC_H
