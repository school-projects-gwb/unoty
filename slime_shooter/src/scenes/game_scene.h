#ifndef DEBUG_APP__GAME_SCENE_H_
#define DEBUG_APP__GAME_SCENE_H_

#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "player/player_movement.h"
#include "entities/scene/scene_background.h"
#include "entities/animator.h"
#include "debug_toggle_script.h"
#include "player/player.h"
#include "ui/hud/hud.h"
#include "entities/ui/ui_button.h"
#include "world/base_object.h"
#include "world/fireplace_object.h"
#include "world/bed_object.h"
#include "enemies/enemy_variants/pink_slime_enemy.h"
#include "enemies/enemy_variants/orange_slime_enemy.h"
#include "enemies/enemy_variants/ghost_enemy.h"

using namespace engine::entities;

namespace slime_shooter {

class GameScene : Scene {
 public:
  static Scene* GameSceneInit() {
    auto* scene = new GameScene();

    // Create SceneBackground
    auto scene_background = std::make_unique<SceneBackground>(
        "resources/sprites/world/tilemap.png", Point{14, 11},
        GameColor::Ui::BackgroundDark);

    // Create GameObjects
    auto music = std::make_unique<AudioSource>("resources/audio/game.mp3");
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);
    scene->SetBackgroundMusic(std::move(music));

    auto base_object = GameObject::Create<BaseObject>();

    auto fireplace_object = GameObject::Create<FireplaceObject>();
    fireplace_object->SetLayer(1);

    auto bed_object = GameObject::Create<BedObject>();
    bed_object->SetLayer(1);

    auto hud = GameObject::Create<Hud>();

    auto player_object = GameObject::Create<Player>();
    player_object->SetLayer(2);

    auto debug_toggler = std::make_shared<DebugToggleScript>();
    scene->AddListener(debug_toggler);

    auto camera = std::make_unique<Camera>();
    camera->SetTrackingTransform(player_object->GetTransform());

    auto pink_enemy = GameObject::Create<PinkSlimeEnemy>();
    pink_enemy->GetTransform()->Position = {875, 500};

    auto orange_enemy = GameObject::Create<OrangeSlimeEnemy>();
    orange_enemy->GetTransform()->Position = {775, 500};

    auto ghost_enemy = GameObject::Create<GhostEnemy>();
    ghost_enemy->GetTransform()->Position = {975, 500};

    scene->AddObject(pink_enemy);
    scene->AddObject(orange_enemy);
    scene->AddObject(ghost_enemy);

    // Add GameObjects to Scene
    scene->AddObject(base_object);
    scene->AddObject(fireplace_object);
    scene->AddObject(bed_object);
    scene->AddObject(player_object);
    scene->AddObject(hud);

    // Add Camera and Background to Scene
    scene->SetCamera(std::move(camera));
    scene->SetBackground(std::move(scene_background));

    return scene;
  }
};

}

#endif //DEBUG_APP__GAME_SCENE_H_
