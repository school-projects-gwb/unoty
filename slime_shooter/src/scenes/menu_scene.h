#ifndef SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_
#define SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_

#include <iostream>
#include "entities/scene/scene_background.h"
#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "entities/animator.h"

#include "ui/menu/buttons/play_game_button.h"
#include "ui/menu/buttons/edit_level_button.h"
#include "ui/menu/buttons/create_level_button.h"
#include "ui/menu/buttons/quit_game_button.h"
#include "ui/menu/buttons/delete_level_button.h"
#include "ui/menu/buttons/play_stress_test_button.h"
#include "ui/menu/buttons/play_platformer_button.h"
#include "ui/menu/buttons/play_particles_button.h"
#include "ui/menu/buttons/play_ai_button.h"
#include "ui/menu/level_selector/level_selector.h"
#include "ui/menu/highscore.h"
#include "ui/button_click_listener.h"

#include "player/player_movement.h"
#include "data_handler/data_object.h"
#include "data_handler/serializer.h"
#include "data_handler/file_handler/file_handler.h"
#include "config/level_loader_config.h"
#include "particle/firework.h"

using namespace engine::entities;
using namespace engine::data_handler;

namespace slime_shooter {

class MenuScene : engine::entities::Scene {
 public:
  static Scene *MenuSceneInit() {
    engine::Engine::GetInstance().SetFps(30);
    scene_ = new MenuScene();

    auto music = std::make_unique<AudioSource>("resources/audio/menu.ogg");
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);
    scene_->SetBackgroundMusic(std::move(music));

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

    auto firework = GameObject::Create<Firework>();

    scene_->AddObject(firework);
    scene_->AddObject(logo_text);
    scene_->AddObject(or_text);

    auto highscore = GameObject::Create<Highscore>();
    scene_->AddObject(highscore);

    auto play_game_button = GameObject::Create<PlayGameButton>();
    auto load_level_button = GameObject::Create<EditLevelButton>();
    auto level_editor_button = GameObject::Create<CreateLevelButton>();
    auto delete_level_button = GameObject::Create<DeleteLevelButton>();
    auto quit_game_button = GameObject::Create<QuitGameButton>();
    auto stress_test_button = GameObject::Create<PlayStressTestButton>();
    auto platformer_button = GameObject::Create<PlayPlatformerButton>();
    auto particles_button = GameObject::Create<PlayParticlesButton>();
    auto ai_button = GameObject::Create<PlayAiButton>();

    scene_->AddObject(play_game_button);
    scene_->AddObject(load_level_button);
    scene_->AddObject(level_editor_button);
    scene_->AddObject(delete_level_button);
    scene_->AddObject(quit_game_button);
    scene_->AddObject(stress_test_button);
    scene_->AddObject(platformer_button);
    scene_->AddObject(particles_button);
    scene_->AddObject(ai_button);

    auto button_click_listener = GameObject::Create<ButtonMouseClickListener>();
    scene_->AddListener(button_click_listener);

    auto debug_toggler = std::make_shared<DebugToggleScript>();
    scene_->AddListener(debug_toggler);

    auto level_selector = GameObject::Create<LevelSelector>(SwitchLevel);
    scene_->AddObject(level_selector);

    CreateScenery();

    scene_->SetCamera(std::move(camera));
    scene_->SetBackground(std::move(scene_background));

    return scene_;
  }

 private:
  static inline Scene* scene_;

  static void CreateScenery() {
    auto fireplace_object = GameObject::Create<FireplaceObject>();
    fireplace_object->GetTransform()->Position = {850, 390};
    for (const auto& child : fireplace_object->GetChildObjects())
      child->GetTransform()->Position -= Vector2d{250,100};

    auto player_object = GameObject::Create<>();
    auto player_sprite = Component::Create<Sprite>("resources/sprites/player/sleeping.png");
    player_object->AddComponent(player_sprite);
    player_object->GetTransform()->SetSize({185, 185});
    player_object->GetTransform()->Position = {920, 370};
    scene_->AddObject(player_object);

    auto sleeping_animation = GameObject::Create<>();
    sleeping_animation->GetTransform()->SetScale(0.6);
    auto animator = Component::Create<Animator>("resources/sprites/player/sleeping_animation.png", 3, Point{32, 32}, Point{2, 2});
    animator->SetSpriteSheetAtIndex("resources/sprites/player/sleeping_animation.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->SetAnimationFrameTimeSeconds(0.6);
    animator->Play(true);
    sleeping_animation->GetTransform()->Position = {1035, 380};
    sleeping_animation->AddComponent(animator);

    auto scene_lighting = std::make_unique<SceneLighting>(Color{128, 0, 128, 255});
    scene_->SetLighting(std::move(scene_lighting));
    scene_->AddObject(fireplace_object);
    scene_->AddObject(sleeping_animation);
  }

  static void SwitchLevel(const std::pair<std::string, std::string> &new_level) {
    GameConfig::SetPropertyValue("active_level_path", new_level.second);
    LevelLoaderConfig::ReloadLevelData();
  }
};

}

#endif //SLIME_SHOOTER_SLIME_SHOOTER_MENU_SCENE_H_
