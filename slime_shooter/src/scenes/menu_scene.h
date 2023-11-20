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
#include "ui/menu/buttons/load_level_button.h"
#include "ui/menu/buttons/level_editor_button.h"
#include "ui/menu/highscore.h"
#include "ui/menu/buttons/button_click_listener.h"

using namespace engine::entities;

namespace slime_shooter {

class MenuScene : engine::entities::Scene {
 public:
  static Scene* MenuSceneInit() {
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

    auto level_label_text = GameObject::Create<UiText>();
    level_label_text->SetContent("LEVEL:");
    level_label_text->GetTransform()->Position = {425, 210};
    level_label_text->SetFont(GameFont::Default, 16);
    level_label_text->SetColor(GameColor::Ui::TextRed);

    auto level_value_text = GameObject::Create<UiText>();
    level_value_text->SetContent("default");
    level_value_text->GetTransform()->Position = {530, 210};
    level_value_text->SetFont(GameFont::Default, 16);
    level_value_text->SetColor(GameColor::Ui::TextWhite);

    scene->AddObject(logo_text);
    scene->AddObject(or_text);
    scene->AddObject(level_label_text);
    scene->AddObject(level_value_text);

    auto highscore = GameObject::Create<Highscore>();
    scene->AddObject(highscore);

    auto play_game_button = GameObject::Create<PlayGameButton>();
    auto load_level_button = GameObject::Create<LoadLevelButton>();
    auto level_editor_button = GameObject::Create<LevelEditorButton>();

    scene->AddObject(play_game_button);
    scene->AddObject(load_level_button);
    scene->AddObject(level_editor_button);

    auto button_click_listener = GameObject::Create<ButtonMouseClickListener>();
    scene->AddListener(button_click_listener);

    scene->SetCamera(std::move(camera));
    scene->SetBackground(std::move(scene_background));

    return scene;
  }
};

}

#endif //SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_
