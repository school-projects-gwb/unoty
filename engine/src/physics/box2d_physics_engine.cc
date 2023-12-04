#include "box2d_physics_engine.h"
#include "entities/scene/scene_manager.h"

namespace engine::physics {

Box2dPhysicsEngine::Box2dPhysicsEngine() {
  //Default world initialization without gravity
  world = new b2World({0.0f, 0.0f});
}

Box2dPhysicsEngine::~Box2dPhysicsEngine() {
   delete world;
}

void Box2dPhysicsEngine::Initialize(const entities::Vector2d& gravity) {
  //todo: if only gravity ever needs to be initialized, rename to SetGravity or Reinitialize
  if (world)
    delete world;

  registered_bodies_.clear();
  world = new b2World({gravity.x, gravity.y});
}

void Box2dPhysicsEngine::ExecutePhysicsStep(float step_time, int velocity_iterations, int position_iterations) {
  world->Step(step_time, velocity_iterations, position_iterations);

  for (auto const& registered_body : registered_bodies_) {
    b2Vec2 position = registered_body.second->GetPosition();

    // Persist the new location calculated by the physics engine to the gameobject's transform
    if (registered_body.first) {
      auto transform = registered_body.first->GetTransform();
      if (transform != nullptr)
        transform->Position = {position.x, position.y};
    }
    else
      world->DestroyBody(registered_body.second);
  }
}

void Box2dPhysicsEngine::RegisterRigidBody(entities::GameObject& game_object, entities::RigidBody& rigid_body) {
  // Use the initial position of the gameobject's transform to initialize the b2body's position
  entities::Vector2d initial_position = game_object.GetTransform()->Position;
  b2BodyDef body_def;
  body_def.type = RigidBodyTypeToBox2D(rigid_body.rb_type); // Set the body type (dynamic, static, or kinematic)
  body_def.position.Set(initial_position.x, initial_position.y);
  b2Body* body = world->CreateBody(&body_def);
  registered_bodies_.emplace(&game_object, body);

  b2PolygonShape shape;
  //todo: Figure out correct conversion from Unoty size to b2 size
  //entities::Point size = game_object.GetTransform()->GetSize();
  //shape.SetAsBox(size.x, size.y);
  shape.SetAsBox(1, 1);

  b2FixtureDef fixture;
  fixture.shape = &shape;
  // Set the density to be non-zero, so dynamic bodies can have forces applied to them, does not affect static/kinematic bodies.
  fixture.density = 1.0f;
  body->CreateFixture(&fixture);
}

void Box2dPhysicsEngine::DeregisterRigidBody(entities::GameObject& game_object) {
  auto it = registered_bodies_.find(&game_object);
  if (it != registered_bodies_.end()) {
    world->DestroyBody(it->second);
    registered_bodies_.erase(&game_object);
  }
}

void Box2dPhysicsEngine::SetRigidBodyAndTransformPosition(entities::GameObject& game_object, const entities::Vector2d& position) {
  game_object.GetTransform()->Position = position;

  auto it = registered_bodies_.find(&game_object);
  if (it != registered_bodies_.end()) {
    it->second->SetTransform(b2Vec2{position.x, position.y}, it->second->GetAngle());
  }
}

void Box2dPhysicsEngine::ApplyForceTowardsDirection(entities::GameObject& game_object, entities::Vector2d direction) {
  auto it = registered_bodies_.find(&game_object);
  if (it != registered_bodies_.end()) {
    it->second->ApplyForceToCenter({direction.x, direction.y}, true);
  }
}

void Box2dPhysicsEngine::ApplyImpulseTowardsDirection(entities::GameObject& game_object, entities::Vector2d direction) {
  auto it = registered_bodies_.find(&game_object);
  if (it != registered_bodies_.end()) {
    it->second->ApplyLinearImpulseToCenter({direction.x, direction.y}, true);
  }
}

void Box2dPhysicsEngine::RegisterCollider(entities::GameObject& game_object, const entities::Collider& collider) {

}

void Box2dPhysicsEngine::DeregisterAllBodies() {
  registered_bodies_.clear();
}

b2BodyType Box2dPhysicsEngine::RigidBodyTypeToBox2D(physics::RigidBodyType rb_type) {
  switch (rb_type) {
    case physics::RigidBodyType::RBDynamic:
      return b2BodyType::b2_dynamicBody;
    case physics::RigidBodyType::RBKinematic:
      return b2BodyType::b2_kinematicBody;
    default:
      return b2BodyType::b2_staticBody;
  }
}

} //namespace engine::physics
