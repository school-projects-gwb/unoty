#include "box2d_physics_engine.h"
#include "entities/scene/scene_manager.h"
#include "box2d_contact_listener.h"
#include "entities/colliders/box_collider.h"
#include "entities/colliders/circle_collider.h"
#include "engine/engine_config.h"
#include "utility/debug.h"

namespace engine::physics {

Box2dPhysicsEngine::Box2dPhysicsEngine(PhysicsConfig config)
: velocity_iterations_(config.velocity_iterations), position_iterations_(config.position_iterations),
  contact_listener_(new Box2dContactListener()) {
  SetStepsPerSecond(config.steps_per_second);
  //Default world initialization without gravity
  world = new b2World(b2Vec2{config.gravity.x, config.gravity.y});
  world->SetContactListener(contact_listener_);
}

Box2dPhysicsEngine::~Box2dPhysicsEngine() {
   delete world;
   delete contact_listener_;
}

void Box2dPhysicsEngine::ExecutePhysicsStep() {
  world->Step(step_time_, velocity_iterations_, position_iterations_);

  for (auto const& registered_body : registered_bodies_) {
    b2Vec2 position = registered_body.second->GetPosition();

    // todo move this logic elsewhere
    if (!registered_body.first->GetIsActive()) {
      registered_body.second->SetEnabled(false);
      continue;
    } else {
      registered_body.second->SetEnabled(true);
    }

    // Persist the new location calculated by the physics engine to the gameobject's transform
    if (registered_body.first) {
      auto transform = registered_body.first->GetTransform();
      if (transform != nullptr)
        transform->Position = {(position.x * GRAPHICS_SCALE_) - GetGameObjectOffsetPosition(registered_body.first).x, (position.y * GRAPHICS_SCALE_) - GetGameObjectOffsetPosition(
            registered_body.first).y};
    }
    else
      world->DestroyBody(registered_body.second);
  }
}

void Box2dPhysicsEngine::SetGravity(const entities::Vector2d& gravity) {
  world->SetGravity({gravity.x, gravity.y});
}

void Box2dPhysicsEngine::RegisterRigidBody(entities::GameObject& game_object, entities::RigidBody& rigid_body) {
  // Use the initial position of the gameobject's transform to initialize the b2body's position
  entities::Vector2d initial_position = game_object.GetTransform()->Position;
  b2BodyDef body_def;
  body_def.type = RigidBodyTypeToBox2D(rigid_body.GetRigidBodyType()); // Set the body type (dynamic, static, or kinematic)
  body_def.position.Set(((initial_position.x + GetGameObjectOffsetPosition(&game_object).x)) * PHYSICS_SCALE_, (initial_position.y + GetGameObjectOffsetPosition(
      &game_object).y) * PHYSICS_SCALE_);
  b2Body* body = world->CreateBody(&body_def);
  body->SetLinearDamping(true);

  registered_bodies_.emplace(&game_object, body);
  reversed_registered_bodies_.emplace(body, &game_object);
}

void Box2dPhysicsEngine::DeregisterRigidBody(entities::GameObject& game_object) {
  auto it = registered_bodies_.find(&game_object);
  b2Body* body_to_remove = nullptr;
  if (it != registered_bodies_.end()) {
    body_to_remove = it->second;
    world->DestroyBody(it->second);
    registered_bodies_.erase(&game_object);
  }

  reversed_registered_bodies_.erase(body_to_remove);
}

void Box2dPhysicsEngine::SetRigidBodyAndTransformPosition(entities::GameObject& game_object, const entities::Vector2d& position) {
  game_object.GetTransform()->Position = position;

  auto it = registered_bodies_.find(&game_object);
  if (it != registered_bodies_.end()) {
    it->second->SetTransform(b2Vec2{(position.x + GetGameObjectOffsetPosition(&game_object).x) * PHYSICS_SCALE_, (position.y + GetGameObjectOffsetPosition(
        &game_object).y)* PHYSICS_SCALE_}, it->second->GetAngle());
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

void Box2dPhysicsEngine::SetLinearVelocity(entities::GameObject& game_object, entities::Vector2d direction) {
  auto it = registered_bodies_.find(&game_object);
  if (it != registered_bodies_.end()) {
    it->second->SetLinearVelocity({direction.x, direction.y});
  }
}

void Box2dPhysicsEngine::RegisterCollider(entities::GameObject& game_object, const entities::Collider& collider) {
  auto it = registered_bodies_.find(&game_object);
  if (it == registered_bodies_.end()) {
    utility::Debug::Log("Cannot add Box2d collider for GameObject with non-existing Box2d physics body.");
    return;
  }
  auto body = it->second;

  if (collider.GetType() == entities::ColliderType::Box) {
    const auto& box_collider = static_cast<const entities::BoxCollider&>(collider);
    RegisterBoxCollider(body, box_collider);
  } else if (collider.GetType() == entities::ColliderType::Circle) {
    const auto& circle_collider = static_cast<const entities::CircleCollider&>(collider);
    RegisterCircleCollider(body, circle_collider);
  }
}

void Box2dPhysicsEngine::RegisterBoxCollider(b2Body *body, const entities::BoxCollider &collider) {
  b2PolygonShape shape;
  shape.SetAsBox(collider.GetSize().x / 2 * PHYSICS_SCALE_, collider.GetSize().y / 2 * PHYSICS_SCALE_);

  b2FixtureDef fixture;
  fixture.filter.categoryBits = 1;
  fixture.filter.maskBits = 1;
  fixture.shape = &shape;
  fixture.density = collider.GetDensity();
  fixture.friction = collider.GetFriction();
  fixture.isSensor = false;

  body->CreateFixture(&fixture);
}

void Box2dPhysicsEngine::RegisterCircleCollider(b2Body *body, const entities::CircleCollider &collider) {
  b2CircleShape shape;
  shape.m_p.Set(0,0);
  shape.m_radius = collider.GetRadius()/2 * PHYSICS_SCALE_;

  b2FixtureDef fixture;
  fixture.filter.categoryBits = 1;
  fixture.filter.maskBits = 1;
  fixture.shape = &shape;
  fixture.density = collider.GetDensity();
  fixture.friction = collider.GetFriction();
  fixture.restitution = 0.0f;
  fixture.isSensor = false;

  body->CreateFixture(&fixture);
}

void Box2dPhysicsEngine::DeregisterAllBodies() {
  for (auto body : registered_bodies_)
    world->DestroyBody(body.second);

  registered_bodies_.clear();
  reversed_registered_bodies_.clear();

  contact_listener_->begin_contacts_.clear();
  contact_listener_->end_contacts_.clear();
}

b2BodyType Box2dPhysicsEngine::RigidBodyTypeToBox2D(physics::RigidBodyType rb_type) {
  switch (rb_type) {
    case physics::RigidBodyType::Dynamic:
      return b2BodyType::b2_dynamicBody;
    case physics::RigidBodyType::Kinematic:
      return b2BodyType::b2_kinematicBody;
    default:
      return b2BodyType::b2_staticBody;
  }
}

std::vector<std::pair<entities::GameObject *, entities::GameObject *>> Box2dPhysicsEngine::GetContactObjects(bool is_start_contacts) const {
  std::vector<std::pair<entities::GameObject*, entities::GameObject*>> colliding_objects;

  auto contacts = is_start_contacts ? contact_listener_->begin_contacts_ : contact_listener_->end_contacts_;
  if (reversed_registered_bodies_.empty()) return {};

  for (const auto& contact : contacts) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    entities::GameObject* gameObjectA = reversed_registered_bodies_.at(fixtureA->GetBody());
    entities::GameObject* gameObjectB = reversed_registered_bodies_.at(fixtureB->GetBody());

    colliding_objects.emplace_back(gameObjectA, gameObjectB);
  }

  return colliding_objects;
}

void Box2dPhysicsEngine::FinalizePhysicsStep() {
  contact_listener_->begin_contacts_.clear();
  contact_listener_->end_contacts_.clear();
}

void Box2dPhysicsEngine::SetStepsPerSecond(int steps_per_second) {
  step_time_ = 1.0f/(float)steps_per_second;
}

entities::Vector2d Box2dPhysicsEngine::GetGameObjectOffsetPosition(entities::GameObject *game_object) {
  auto size = game_object->GetTransform()->GetSize();
  if (size.x != 0 && size.y != 0) return {size.x/2, size.y/2};

  auto collider = game_object->GetComponentByType<entities::Collider>();
  if (!collider) return {0,0};

  if (collider->GetType() == entities::ColliderType::Box) {
    const auto& box_collider = static_cast<const entities::BoxCollider&>(*collider);
    return box_collider.GetSize() / 2;
  } else if (collider->GetType() == entities::ColliderType::Circle) {
    const auto& circle_collider = static_cast<const entities::CircleCollider&>(*collider);
    return {circle_collider.GetRadius() / 2, circle_collider.GetRadius() / 2};
  }
}

} //namespace engine::physics
