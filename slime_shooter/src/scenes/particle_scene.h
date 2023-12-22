#ifndef SLIME_SHOOTER_SRC_SCENES_PARTICLE_SCENE_H
#define SLIME_SHOOTER_SRC_SCENES_PARTICLE_SCENE_H

#include "entities/scene/scene.h"
#include "engine/engine.h"
#include "showcase/particle/stress_emitter.h"
#include "showcase/particle/particle_debugger.h"

namespace slime_shooter::showcase {
class ParticleScene : engine::entities::Scene {
 public:
  static Scene *ParticleSceneInit() {
    engine::Engine::GetInstance().SetFps(60);
    scene_ = new ParticleScene();

    auto stress_emitter = GameObject::Create<StressEmitter>();
    scene_->AddObject(stress_emitter);

    auto particle_debugger = std::make_shared<ParticleDebugger>(stress_emitter);
    scene_->AddListener(particle_debugger);

    GenerateUI();

    return scene_;
  }

 private:
  static inline Scene* scene_;

  static void GenerateUI(){
    auto stress_test_debug_text = GameObject::Create<UiText>();

    stress_test_debug_text->GetTransform()->Position = {15, 75};
    stress_test_debug_text->GetTransform()->SetScale(0.75);
    stress_test_debug_text->SetColor(GameColor::Green::Shade4);

    stress_test_debug_text->SetContent("Press (SPACE) to launch a firework. Press (P) to go back to the main menu.");
    stress_test_debug_text->SetFont(GameFont::Default, 14);
    stress_test_debug_text->SetName("stress_test_debug_text");

    scene_->AddObject(stress_test_debug_text);

  }
};
}
#endif //SLIME_SHOOTER_SRC_SCENES_PARTICLE_SCENE_H
