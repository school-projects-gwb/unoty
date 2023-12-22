#ifndef SLIME_SHOOTER_SRC_SCENES_SHOWCASE_SLIME_SHOOTER_SRC_SCENES_SHOWCASE_PLATFORMER_SCENE_H_
#define SLIME_SHOOTER_SRC_SCENES_SHOWCASE_SLIME_SHOOTER_SRC_SCENES_SHOWCASE_PLATFORMER_SCENE_H_

#include "entities/scene/scene.h"
#include "entities/physics/box_collider.h"
#include "showcase/platformer/player.h"
#include "entities/ui/ui_object.h"
#include "showcase/platformer/camera_target.h"

using namespace engine::entities;

namespace slime_shooter::showcase {

class PlatformerScene : Scene {
 public:
  static Scene *PlatformerSceneInit() {
    engine::Engine::GetInstance().SetFps(engine::EngineConfig::game_tick_fps);
    engine::Engine::GetInstance().GetPhysicsEngine()->SetGravity({0, 350});
    scene_ = new PlatformerScene();

    CreatePlatform({20, 1280}, {0, -100}, false);
    CreatePlatform({1280, 20}, {0, 500}, false);
    CreatePlatform({200, 20}, {175, 425});
    CreatePlatform({200, 20}, {950, 400});

    auto background_object = GameObject::Create();
    auto background_sprite = Component::Create<Sprite>("resources/sprites/world/platformer_background.png");
    background_object->AddComponent(background_sprite);
    background_object->GetTransform()->SetSize({1280, 300});
    background_object->GetTransform()->Position = {0 - 640, 350};
    background_object->SetLayer(2);
    scene_->AddObject(background_object);

    auto fireplace_object = GameObject::Create();
    fireplace_object->GetTransform()->Position = {530, 350};

    auto animator = Component::Create<Animator>("resources/sprites/world/fireplace.png", 3, Point{16, 16}, Point{3, 1});
    animator->SetSpriteSheetAtIndex("resources/sprites/world/fireplace_2d.png", 0);
    animator->SetCurrentAnimationSpriteSheet(0);
    animator->SetAnimationFrameTimeSeconds(0.4);
    animator->Play(true);

    auto fireplace_light_object = GameObject::Create();
    auto light = Component::Create<LightSource>("resources/sprites/light_sources/yellow.png");
    light->GetSprite().SetColor({255, 149, 110});
    fireplace_light_object->GetTransform()->SetSize({350, 350});
    fireplace_light_object->GetTransform()->Position = fireplace_object->GetTransform()->Position - Vector2d{250, 250};
    fireplace_light_object->AddComponent(light);

    fireplace_object->AddChildObject(fireplace_light_object);
    fireplace_object->AddComponent(animator);

    scene_->AddObject(fireplace_object);

    CreateSprites({90, 90},
                  "resources/sprites/world/stars/star.png",
                  {{410, 100}, {575, 50}, {750, 50}, {1100, 0}, {1100, -350}, {500, -250}});
    CreateSprites({45, 45}, "resources/sprites/world/stars/star_2.png", {{435, 40}, {635, 50}, {150, 65}, {435, -200}});
    CreateSprites({50, 50}, "resources/sprites/world/stars/star_3.png", {{480, 80}, {635, 515}});
    CreateSprites({50, 50}, "resources/sprites/world/stars/star_4.png", {{550, 80}, {385, 540}});
    CreateSprites({80, 80}, "resources/sprites/world/stars/star_5.png", {{860, 15}, {960, -35}, {725, 555}});
    CreateSprites({200, 80},
                  "resources/sprites/world/cloud.png",
                  {{50, -350}, {960, -275}, {725, -150}, {600, -350}},
                  false);

    auto player = GameObject::Create<Player>();
    player->GetTransform()->Position = {0, 210};
    scene_->AddObject(player);

    auto scene_lighting = std::make_unique<SceneLighting>(Color{0, 0, 0, 115});
    scene_->SetLighting(std::move(scene_lighting));

    auto camera = std::make_unique<Camera>();
    auto camera_transform = camera->GetTransform();

    auto camera_target = GameObject::Create<CameraTarget>(camera->GetTransform());
    scene_->AddObject(camera_target);

    scene_->SetCamera(std::move(camera));

    auto debug_toggler = std::make_shared<DebugToggleScript>();
    scene_->AddListener(debug_toggler);

    auto music = std::make_unique<AudioSource>("resources/audio/platformer_soundtrack.mp3");
    music->play_on_wake_ = true;
    music->ToggleLooping();
    music->SetVolume(20);
    scene_->SetBackgroundMusic(std::move(music));

    return scene_;
  }

 private:
  static inline Scene *scene_;

  static void CreateSprites(Point sprite_size,
                            const std::string &sprite_path,
                            const std::vector<Vector2d> &positions,
                            bool with_light = true) {
    for (auto position : positions) {
      auto sprite = Component::Create<Sprite>(sprite_path);

      auto sprite_object = GameObject::Create();
      sprite_object->GetTransform()->Position = position;
      sprite_object->GetTransform()->SetSize(sprite_size);
      sprite_object->AddComponent(sprite);

      scene_->AddObject(sprite_object);

      if (!with_light) continue;

      auto light = Component::Create<LightSource>("resources/sprites/light_sources/yellow.png");
      light->GetSprite().SetColor({170, 225, 250, 255});

      auto light_object = GameObject::Create();
      light_object->GetTransform()->Position = sprite_object->GetTransform()->Position;
      light_object->GetTransform()->SetSize(sprite_size);
      light_object->AddComponent(light);

      sprite_object->AddChildObject(light_object);
    }
  }

  static void CreatePlatform(Point size, Point position, bool has_sprite = true) {
    auto platform = GameObject::Create();
    auto collider = Component::Create<BoxCollider>(Vector2d{size.x, size.y / 2});
    auto rigid_body = Component::Create<RigidBody>(*platform, engine::physics::RigidBodyType::Static, collider);
    rigid_body->SetPosition(Vector2d{position.x - 50, position.y - 50});
    platform->AddComponent(rigid_body);
    platform->AddComponent(collider);
    platform->SetTagName("Platform");

    scene_->AddObject(platform);

    if (!has_sprite) return;

    auto sprite_object = GameObject::Create();;
    sprite_object->GetTransform()->SetSize(size);
    sprite_object->GetTransform()->Position = {position.x - size.x / 2, position.y - size.y / 2};

    auto sprite = Component::Create<Sprite>("resources/sprites/world/platform.png");
    sprite_object->AddComponent(sprite);

    scene_->AddObject(sprite_object);
  }
};

}

#endif //SLIME_SHOOTER_SRC_SCENES_SHOWCASE_SLIME_SHOOTER_SRC_SCENES_SHOWCASE_PLATFORMER_SCENE_H_
