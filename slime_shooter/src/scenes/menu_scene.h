#ifndef SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_
#define SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_

#include <iostream>
#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "player/player_movement.h"
#include "entities/scene/scene_background.h"
#include "entities/animator.h"
#include "ui/menu/buttons/play_game_button.h"
#include "ui/menu/buttons/edit_level_button.h"
#include "ui/menu/buttons/create_level_button.h"
#include "ui/menu/highscore.h"
#include "ui/button_click_listener.h"
#include "data_handler/data_object.h"
#include "data_handler/serializer.h"
#include "data_handler/file_handler/file_handler.h"
#include "config/level_loader_config.h"
#include "ui/menu/level_selector/level_selector.h"
#include "ui/menu/buttons/quit_game_button.h"
#include "ui/menu/buttons/delete_level_button.h"

using namespace engine::entities;
using namespace engine::data_handler;

namespace slime_shooter {

class MenuScene : engine::entities::Scene {
 public:
  static Scene* MenuSceneInit() {
    engine::Engine::GetInstance().SetFps(30);
    auto* scene = new MenuScene();

    auto music = std::make_unique<AudioSource>("resources/audio/menu.mp3");
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);
    scene->SetBackgroundMusic(std::move(music));
    
    auto scene_background = std::make_unique<SceneBackground>(GameColor::Ui::BackgroundDark);
    auto camera = std::make_unique<Camera>();

    auto logo_text = GameObject::Create<UiText>();
    logo_text->SetContent("SLIME SHOOTER");
    logo_text->GetTransform()->Position = {100, 100};
    logo_text->SetFont(GameFont::Default, 42);
    logo_text->SetColor(GameColor::Ui::TextGreen);

    auto or_text = GameObject::Create<UiText>();
    or_text->SetContent("OR");
    or_text->GetTransform()->Position = {230, 275};
    or_text->SetFont(GameFont::Default, 20);
    or_text->SetColor(GameColor::Ui::TextGray);

    scene->AddObject(logo_text);
    scene->AddObject(or_text);

    auto highscore = GameObject::Create<Highscore>();
    scene->AddObject(highscore);

    auto play_game_button = GameObject::Create<PlayGameButton>();
    auto load_level_button = GameObject::Create<EditLevelButton>();
    auto level_editor_button = GameObject::Create<CreateLevelButton>();
    auto delete_level_button = GameObject::Create<DeleteLevelButton>();
    auto quit_game_button = GameObject::Create<QuitGameButton>();

    scene->AddObject(play_game_button);
    scene->AddObject(load_level_button);
    scene->AddObject(level_editor_button);
    scene->AddObject(delete_level_button);
    scene->AddObject(quit_game_button);

    auto button_click_listener = GameObject::Create<ButtonMouseClickListener>();
    scene->AddListener(button_click_listener);

    auto debug_toggler = std::make_shared<DebugToggleScript>();
    scene->AddListener(debug_toggler);

    auto level_selector = GameObject::Create<LevelSelector>(SwitchLevel);
    scene->AddObject(level_selector);

    scene->SetCamera(std::move(camera));
    scene->SetBackground(std::move(scene_background));

    return scene;
  }

  static void SwitchLevel(const std::pair<std::string, std::string>& new_level) {
    GameConfig::SetPropertyValue("active_level_path", new_level.second);
    LevelLoaderConfig::ReloadLevelData();
  }
};

}

#endif //SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_
