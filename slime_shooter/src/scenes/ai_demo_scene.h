
#ifndef SLIME_SHOOTER_SRC_SCENES_AI_DEMO_SCENE_H
#define SLIME_SHOOTER_SRC_SCENES_AI_DEMO_SCENE_H

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
#include "structures/base_object.h"
#include "structures/fireplace_object.h"
#include "structures/bed_object.h"
#include "enemies/enemy_spawner_logic.h"
#include "enemies/enemy_spawner.h"
#include "config/level_loader_config.h"
#include "upgrades/base_upgrade.h"
#include "ui/popup/popup.h"
#include "ui/button_click_listener.h"
#include "entities/foresight_camera.h"
#include "structures/wall.h"
#include "player/ai_demo_player.h"
#include "structures/ghost-wall.h"

using namespace engine::entities;

namespace slime_shooter {

class AiDemoScene : Scene {
 public:
  static Scene *AiDemoSceneInit() {
    engine::Engine::GetInstance().SetFps(60);
    scene_ = new AiDemoScene();
    scene_->SetViewportRendering(true, 0);

    // Create SceneBackground
    TileMapConfig tile_map_config;
    tile_map_config.tile_map_image_path = LevelLoaderConfig::GetPropertyValue("tile_map_path");
    tile_map_config.tile_map_col_row_amount = Point{9, 5};
    tile_map_config.tile_render_pixel_size = {128, 128};
    tile_map_config.background_color = GameColor::Ui::BackgroundDark;

    auto scene_background = std::make_unique<SceneBackground>(tile_map_config);

    // Create GameObjects
    auto music = std::make_unique<AudioSource>(
        LevelLoaderConfig::GetPropertyValue("background_music_path"));
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);

    CreateWalls();

    auto camera = std::make_unique<Camera>();

    auto player = GameObject::Create<AiDemoPlayer>();
    player->SetLayer(3);

    // Add objects to Scene
    scene_->SetCamera(std::move(camera));
    scene_->SetBackground(std::move(scene_background));
    scene_->SetBackgroundMusic(std::move(music));

    scene_->AddObject(player);

    return scene_;
  }

 private:
  static inline Scene *scene_;

  static void CreateWalls() {
    Point size = {50, 50};
    Vector2d position;
    char map[10][10] = {
        {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
        {'w', ' ', ' ', 'w', ' ', ' ', 'w', 'w', 'w', 'w'},
        {'w', 'w', ' ', ' ', ' ', 'w', 'w', ' ', ' ', 'w'},
        {'w', ' ', ' ', 'w', ' ', ' ', ' ', ' ', 'w', 'w'},
        {'w', ' ', 'w', 'w', ' ', 'w', ' ', 'w', 'w', 'w'},
        {' ', ' ', 'w', 'w', 'w', 'w', ' ', 'w', ' ', ' '},
        {'w', ' ', ' ', 'w', 'w', ' ', ' ', 'n', ' ', 'w'},
        {'w', 'w', ' ', ' ', 'w', ' ', 'w', ' ', ' ', 'w'},
        {'w', 'w', 'w', ' ', 'w', ' ', ' ', ' ', 'w', 'w'},
        {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'}
    };

    for (int y = 0; y < 10; y++) {
      for(int x = 0; x < 10; x++) {
        char n = map[y][x];
        if(n == 'w'){
          position = {(size.x * x) + 400, (size.y * y) + 100};
          auto wall = GameObject::Create<Wall>(size, position);

          scene_->AddObject(wall);
        } else if(n == 'n'){
          position = {(size.x * x) + 400, (size.y * y) + 100};
          auto wall = GameObject::Create<GhostWall>(size, position);

          scene_->AddObject(wall);
        }
      }
    }
  }
};

}

#endif //SLIME_SHOOTER_SRC_SCENES_AI_DEMO_SCENE_H
