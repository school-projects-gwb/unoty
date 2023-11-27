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
#include "player_base/base_object.h"
#include "player_base/fireplace_object.h"
#include "player_base/bed_object.h"
#include "enemies/enemy_spawner_logic.h"
#include "enemies/enemy_spawner.h"
#include "config/level_loader_config.h"
#include "upgrades/base_upgrade.h"

using namespace engine::entities;

namespace slime_shooter {

class GameScene : Scene {
 public:
  static Scene* GameSceneInit() {
    engine::Engine::GetInstance().SetFps(60);
    scene_ = new GameScene();

    // Create SceneBackground
    TileMapConfig tile_map_config;
    tile_map_config.tile_map_image_path = LevelLoaderConfig::GetPropertyValue("tile_map_path");
    tile_map_config.tile_map_col_row_amount = Point{14, 11};
    tile_map_config.tile_render_pixel_size = {128, 128};
    tile_map_config.background_color = GameColor::Ui::BackgroundDark;

    auto scene_background = std::make_unique<SceneBackground>(tile_map_config);

    // Create GameObjects
    auto music = std::make_unique<AudioSource>(
        LevelLoaderConfig::GetPropertyValue("background_music_path"));
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);
    scene_->SetBackgroundMusic(std::move(music));

    LoadBaseObjects();
    LoadUpgrades();

    auto hud = GameObject::Create<Hud>();

    auto player_object = GameObject::Create<Player>();
    player_object->SetLayer(3);

    auto debug_toggler = std::make_shared<DebugToggleScript>();
    scene_->AddListener(debug_toggler);

    auto camera = std::make_unique<Camera>();
    camera->SetTrackingTransform(player_object->GetTransform());

    auto enemy_spawner = GameObject::Create<EnemySpawner>();

    // Add GameObjects to Scene
    scene_->AddObject(player_object);
    scene_->AddObject(hud);
    scene_->AddObject(enemy_spawner);

    // Add Camera and Background to Scene
    scene_->SetCamera(std::move(camera));
    scene_->SetBackground(std::move(scene_background));

    return scene_;
  }

 private:
  static inline Scene* scene_;

  static void LoadBaseObjects() {
    auto base_object = GameObject::Create<BaseObject>();

    auto fireplace_object = GameObject::Create<FireplaceObject>();
    fireplace_object->SetLayer(1);

    auto bed_object = GameObject::Create<BedObject>();
    bed_object->SetLayer(1);

    scene_->AddObject(base_object);
    scene_->AddObject(fireplace_object);
    scene_->AddObject(bed_object);
  }

  static void LoadUpgrades() {
    std::string speed_upgrade_position = LevelLoaderConfig::GetPropertyValue("speed_upgrade");
    std::string health_upgrade_position = LevelLoaderConfig::GetPropertyValue("health_upgrade");

    if (speed_upgrade_position != LevelLoaderConfig::EmptyValue()) {
      auto speed_upgrade = GameObject::Create<BaseUpgrade>(
          statistic_upgrades::GetStatisticUpgrade("Speed"),
          LevelLoaderConfig::GetPositionFromString(speed_upgrade_position));
      speed_upgrade->SetLayer(2);
      scene_->AddObject(speed_upgrade);
    }

    if (health_upgrade_position != LevelLoaderConfig::EmptyValue()) {
      auto health_upgrade = GameObject::Create<BaseUpgrade>(
          statistic_upgrades::GetStatisticUpgrade("Health"),
          LevelLoaderConfig::GetPositionFromString(health_upgrade_position));
      health_upgrade->SetLayer(2);
      scene_->AddObject(health_upgrade);
    }
  }
};

}

#endif //DEBUG_APP__GAME_SCENE_H_
