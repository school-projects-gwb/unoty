#ifndef SLIME_SHOOTER_SRC_SCENES_SLIME_SHOOTER_SRC_SCENES_LEVEL_EDITOR_SCENE_H_
#define SLIME_SHOOTER_SRC_SCENES_SLIME_SHOOTER_SRC_SCENES_LEVEL_EDITOR_SCENE_H_

#include <utility>

#include "entities/scene/scene.h"
#include "entities/game_object.h"
#include "entities/sprite.h"
#include "entities/behaviour_script.h"
#include "entities/scene/scene_background.h"
#include "ui/button_click_listener.h"
#include "common/definitions.h"
#include "ui/level_editor/buttons/back_button.h"
#include "ui/level_editor/buttons/save_level_button.h"
#include "ui/level_editor/tilemap_selector/tilemap_selector.h"
#include "ui/level_editor/audio_selector/audio_selector.h"
#include "unordered_map"
#include "config/level_loader_config.h"
#include "config/level_editor_config.h"
#include "debug_toggle_script.h"
#include "ui/level_editor/editor_objects/drag_handler.h"

using namespace engine::entities;

namespace slime_shooter {

class LevelEditorScene : engine::entities::Scene {
 public:
  static Scene* LevelEditorSceneInit() {
    engine::Engine::GetInstance().SetFps(30);
    scene_ = new LevelEditorScene();
    is_new_level_ = LevelEditorConfig::IsNewLevel();

    LoadUiElements();
    LoadDraggableObjects();

    auto audio_path = LevelEditorConfig::IsNewLevel() ?
        "resources/audio/game.mp3" : LevelLoaderConfig::GetPropertyValue("background_music_path");
    scene_->SetBackgroundMusic(CreateSceneBackgroundMusic(audio_path));

    auto base_object = GameObject::Create<>();
    base_object->GetTransform()->SetSize({235, 175});
    base_object->GetTransform()->Position = {120, 105};

    auto base_sprite = Component::Create<Sprite>("resources/sprites/world/floor.png");
    base_object->AddComponent(base_sprite);

    scene_->AddObject(base_object);

    auto debug_toggler = std::make_shared<DebugToggleScript>();
    scene_->AddListener(debug_toggler);

    auto camera = std::make_unique<Camera>();
    scene_->SetCamera(std::move(camera));

    auto tile_map_path = LevelEditorConfig::IsNewLevel() ?
        "resources/sprites/world/tilemap.png" : LevelLoaderConfig::GetPropertyValue("tile_map_path");
    scene_->SetBackground(CreateSceneBackground(tile_map_path));

    auto drag_handler = std::make_shared<DragHandler>();
    scene_->AddListener(drag_handler);

    return scene_;
  }

 private:
  static inline Scene* scene_;
  static inline std::unordered_map<std::string, std::string> level_values_;
  static inline bool is_new_level_;

  static void UpdateTileMapImage(const std::string& image_path) {
    level_values_["tile_map_path"] = image_path;
    scene_->SetBackground(CreateSceneBackground(image_path));
  }

  static void UpdateAudio(const std::string& audio_path) {
    level_values_["background_music_path"] = audio_path;
    scene_->SetBackgroundMusic(CreateSceneBackgroundMusic(audio_path));
  }

  static std::unique_ptr<SceneBackground> CreateSceneBackground(std::string image_path) {
    TileMapConfig tile_map_config;
    tile_map_config.tile_map_image_path = std::move(image_path);
    tile_map_config.tile_map_col_row_amount = Point{14, 11};
    tile_map_config.tile_render_pixel_size = {46, 48};
    tile_map_config.background_color = GameColor::Ui::BackgroundDark;

    return std::make_unique<SceneBackground>(tile_map_config);
  }

  static std::unique_ptr<AudioSource> CreateSceneBackgroundMusic(const std::string &audio_path) {
    auto music = std::make_unique<AudioSource>(audio_path);
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);
    music->Play();
    return music;
  }

  static void TriggerSaveLevel() {
    for (const auto& object : scene_->GetObjectsByTagName("draggable_object")) {
      auto draggable_object = GameObject::Cast<DraggableObject>(object);
      auto world_position = LevelLoaderConfig::GetWorldPositionFromEditorPosition(draggable_object->GetTransform()->Position);
      level_values_[draggable_object->key_name] = LevelLoaderConfig::StringifyPosition(world_position);
    }

    LevelEditorConfig::SaveLevel(level_values_);
    engine::Engine::GetInstance().SetActiveScene("menu_scene");
  }

  static void LoadUiElements() {
    auto level_editor_title = GameObject::Create<UiText>();
    level_editor_title->SetContent(is_new_level_ ? "LEVEL EDITOR: CREATING NEW" : "LEVEL EDITOR: EDITING EXISTING");
    level_editor_title->GetTransform()->Position = {675, 620};
    level_editor_title->SetFont(GameFont::Default, 18);
    level_editor_title->SetColor(GameColor::Ui::TextPink);
    scene_->AddObject(level_editor_title);

    auto back_button = GameObject::Create<BackButton>();
    scene_->AddObject(back_button);

    auto save_level_button = GameObject::Create<SaveLevelButton>(TriggerSaveLevel);
    scene_->AddObject(save_level_button);

    auto tile_map_selector = GameObject::Create<TilemapSelector>(UpdateTileMapImage);
    scene_->AddObject(tile_map_selector);

    auto audio_selector = GameObject::Create<AudioSelector>(UpdateAudio);
    scene_->AddObject(audio_selector);

    auto button_click_listener = GameObject::Create<ButtonMouseClickListener>();
    scene_->AddListener(button_click_listener);
  }

  static void LoadDraggableObjects() {
    LoadDraggableObject("speed_upgrade", "resources/sprites/world/speedbuff.png",
               is_new_level_ ? "651,755" : LevelLoaderConfig::GetPropertyValue("speed_upgrade"));
    LoadDraggableObject("health_upgrade", "resources/sprites/world/health-regen.png",
               is_new_level_ ? "1165,755" : LevelLoaderConfig::GetPropertyValue("health_upgrade"));
  }

  static void LoadDraggableObject(const std::string& key_name, const std::string& upgrade_sprite_path, const std::string& position) {
    auto draggable_object = GameObject::Create<DraggableObject>();
    draggable_object->sprite_path = upgrade_sprite_path;
    draggable_object->position_in_editor = LevelLoaderConfig::GetEditorPositionFromString(position);
    draggable_object->key_name = key_name;
    draggable_object->GetTransform()->SetSize(Point{45, 45});
    draggable_object->GetTransform()->Position = draggable_object->position_in_editor;
    draggable_object->SetTagName("draggable_object");
    draggable_object->SetLayer(2);

    auto symbol_sprite = Component::Create<Sprite>(draggable_object->sprite_path);
    draggable_object->AddComponent(symbol_sprite);
    scene_->AddObject(draggable_object);
  }
};

}

#endif //SLIME_SHOOTER_SRC_SCENES_SLIME_SHOOTER_SRC_SCENES_LEVEL_EDITOR_SCENE_H_
