#ifndef SLIME_SHOOTER_SRC_SCENES_SHOWCASE_SLIME_SHOOTER_SRC_SCENES_SHOWCASE_LIGHT_SCENE_H_
#define SLIME_SHOOTER_SRC_SCENES_SHOWCASE_SLIME_SHOOTER_SRC_SCENES_SHOWCASE_LIGHT_SCENE_H_

#include "entities/scene/scene.h"
#include "entities/physics/box_collider.h"
#include "showcase/platformer/player.h"
#include "entities/ui/ui_object.h"

using namespace engine::entities;

namespace slime_shooter::showcase {

class LightScene : Scene {
 public:
  static Scene* LightSceneInit() {
    engine::Engine::GetInstance().SetFps(60);
    engine::Engine::GetInstance().GetPhysicsEngine()->SetGravity({0, 350});
    scene_ = new LightScene();

    auto bottom_wall = GameObject::Create();

    auto bottom_wall_collider = Component::Create<BoxCollider>(Vector2d{1280, 10});
    auto bottom_wall_body = Component::Create<RigidBody>(*bottom_wall, engine::physics::RigidBodyType::Static, bottom_wall_collider);
    bottom_wall_body->SetPosition(Vector2d{0,625});
    bottom_wall->AddComponent(bottom_wall_body);
    bottom_wall->AddComponent(bottom_wall_collider);
    bottom_wall->SetTagName("Wall");

    auto bottom_wall_sprite = GameObject::Create<UiObject>();
    bottom_wall_sprite->SetBackgroundColor(GameColor::Orange::Shade1);
    bottom_wall_sprite->GetTransform()->SetSize({1280, 20});
    bottom_wall_sprite->GetTransform()->Position = {0, 675};

    auto left_platform = GameObject::Create();
    auto left_platform_collider = Component::Create<BoxCollider>(Vector2d{200, 10});
    auto left_platform_body = Component::Create<RigidBody>(*left_platform, engine::physics::RigidBodyType::Static, left_platform_collider);
    left_platform_body->SetPosition(Vector2d{250,475});
    left_platform->AddComponent(left_platform_body);
    left_platform->AddComponent(left_platform_collider);
    left_platform->SetTagName("Wall");

    auto left_platform_sprite = GameObject::Create<UiObject>();
    left_platform_sprite->SetBackgroundColor(GameColor::Coral::Shade1);
    left_platform_sprite->GetTransform()->SetSize({200, 20});
    left_platform_sprite->GetTransform()->Position = {250, 525};

    auto right_platform = GameObject::Create();
    auto right_platform_collider = Component::Create<BoxCollider>(Vector2d{200, 10});
    auto right_platform_body = Component::Create<RigidBody>(*right_platform, engine::physics::RigidBodyType::Static, right_platform_collider);
    right_platform_body->SetPosition(Vector2d{600, 350});
    right_platform->AddComponent(right_platform_body);
    right_platform->AddComponent(right_platform_collider);
    right_platform->SetTagName("Wall");

    auto right_platform_sprite = GameObject::Create<UiObject>();
    right_platform_sprite->SetBackgroundColor(GameColor::Coral::Shade4);
    right_platform_sprite->GetTransform()->SetSize({200, 20});
    right_platform_sprite->GetTransform()->Position = {600, 400};

    auto player = GameObject::Create<Player>();
    player->GetTransform()->Position = {0,210};
    scene_->AddObject(player);

    scene_->AddObject(bottom_wall);
    scene_->AddObject(bottom_wall_sprite);

    scene_->AddObject(left_platform);
    scene_->AddObject(left_platform_sprite);

    scene_->AddObject(right_platform);
    scene_->AddObject(right_platform_sprite);

    return scene_;
  }

 private:
  static inline Scene* scene_;
};

}

#endif //SLIME_SHOOTER_SRC_SCENES_SHOWCASE_SLIME_SHOOTER_SRC_SCENES_SHOWCASE_LIGHT_SCENE_H_
