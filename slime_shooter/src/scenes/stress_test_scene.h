#ifndef SLIME_SHOOTER_SRC_SCENES_STRESS_TEST_SCENE_H
#define SLIME_SHOOTER_SRC_SCENES_STRESS_TEST_SCENE_H

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

using namespace engine::entities;

namespace slime_shooter {

class StressTestScene : Scene {
 public:
  static Scene *StressTestSceneInit() {
    engine::Engine::GetInstance().SetFps(engine::EngineConfig::game_tick_fps);
    engine::Engine::GetInstance().GetPhysicsEngine()->SetGravity({0, 0});
    scene_ = new StressTestScene();
    scene_->SetViewportRendering(true, -250);
    StressTestConfig::stress_test_enabled = true;
    StressTestConfig::alive_enemies = 0;
    StressTestConfig::enemy_pool_size = 0;

    // Create SceneBackground
    TileMapConfig tile_map_config;
    tile_map_config.tile_map_image_path = LevelLoaderConfig::GetPropertyValue("tile_map_path");
    tile_map_config.tile_map_col_row_amount = Point{14, 11};
    tile_map_config.tile_render_pixel_size = {128, 128};
    tile_map_config.background_color = GameColor::Ui::TextRed;

    auto scene_background = std::make_unique<SceneBackground>(tile_map_config);
    auto scene_lighting = std::make_unique<SceneLighting>(Color{255, 0, 100, 150});

    // Create GameObjects
    auto music = std::make_unique<AudioSource>(
        LevelLoaderConfig::GetPropertyValue("background_music_path"));
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);
    scene_->SetBackgroundMusic(std::move(music));

    auto hud = GameObject::Create<Hud>(true);

    auto player_object = GameObject::Create<Player>(engine::physics::RigidBodyType::Kinematic);
    player_object->SetLayer(3);

    auto debug_toggler = std::make_shared<DebugToggleScript>();
    scene_->AddListener(debug_toggler);

    auto camera = std::make_unique<ForesightCamera>(10, 1.5);
    camera->SetTrackingTransform(player_object->GetTransform());

    auto enemy_spawner = GameObject::Create<EnemySpawner>();
    enemy_spawner->SetSpawnRate(0.01f);

    // Add GameObjects to Scene
    scene_->AddObject(player_object);
    scene_->AddObject(hud);
    scene_->AddObject(enemy_spawner);

    auto popup = GameObject::Create<Popup>();
    popup->SetLayer(5);
    scene_->AddObject(popup);

    auto game_over_popup = GameObject::Create<GameOverPopup>();
    game_over_popup->SetLayer(5);
    scene_->AddObject(game_over_popup);

    auto upgrade_handler = GameObject::Create<UpgradeHandler>();
    upgrade_handler->SetLayer(5);
    scene_->AddObject(upgrade_handler);

    auto button_click_listener = GameObject::Create<ButtonMouseClickListener>();
    scene_->AddListener(button_click_listener);

    // Add Camera and Background to Scene
    scene_->SetCamera(std::move(camera));
    scene_->SetBackground(std::move(scene_background));
    scene_->SetLighting(std::move(scene_lighting));

    return scene_;
  }

 private:
  static inline Scene *scene_;

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

  static void CreateWalls() {
    auto top_wall = GameObject::Create();
    top_wall->GetTransform()->SetSize(Point{1792, 30});
    auto top_wall_collider = Component::Create<BoxCollider>(Vector2d{1792, 64});
    auto top_wall_body =
        Component::Create<RigidBody>(*top_wall, engine::physics::RigidBodyType::Static, top_wall_collider);
    top_wall_body->SetPosition(Vector2d{0, 0});
    top_wall->AddComponent(top_wall_body);
    top_wall->AddComponent(top_wall_collider);
    top_wall->SetTagName("Wall");

    auto left_wall = GameObject::Create();
    auto left_wall_collider = Component::Create<BoxCollider>(Vector2d{64, 1200});
    auto left_wall_body =
        Component::Create<RigidBody>(*left_wall, engine::physics::RigidBodyType::Static, left_wall_collider);
    left_wall_body->SetPosition(Vector2d{0, 90});
    left_wall->AddComponent(left_wall_body);
    left_wall->AddComponent(left_wall_collider);
    left_wall->SetTagName("Wall");

    auto bottom_wall = GameObject::Create();
    auto bottom_wall_collider = Component::Create<BoxCollider>(Vector2d{1792, 30});
    auto bottom_wall_body =
        Component::Create<RigidBody>(*bottom_wall, engine::physics::RigidBodyType::Static, bottom_wall_collider);
    bottom_wall_body->SetPosition(Vector2d{0, 1370});
    bottom_wall->AddComponent(bottom_wall_body);
    bottom_wall->AddComponent(bottom_wall_collider);
    bottom_wall->SetTagName("Wall");

    auto right_wall = GameObject::Create();
    auto right_wall_collider = Component::Create<BoxCollider>(Vector2d{30, 1200});
    auto right_wall_body =
        Component::Create<RigidBody>(*right_wall, engine::physics::RigidBodyType::Static, right_wall_collider);
    right_wall_body->SetPosition(Vector2d{1760, 90});
    right_wall->AddComponent(right_wall_body);
    right_wall->AddComponent(right_wall_collider);
    right_wall->SetTagName("Wall");

    scene_->AddObject(top_wall);
    scene_->AddObject(left_wall);
    scene_->AddObject(bottom_wall);
    scene_->AddObject(right_wall);
  }

};

}

#endif //SLIME_SHOOTER_SRC_SCENES_STRESS_TEST_SCENE_H
