#ifndef ENGINE_SRC_PHYSICS_ENGINE_SRC_PHYSICS_BOX2D_CONTACT_LISTENER_H_
#define ENGINE_SRC_PHYSICS_ENGINE_SRC_PHYSICS_BOX2D_CONTACT_LISTENER_H_

#include <box2d/box2d.h>
#include "iostream"

namespace engine::physics {

class Box2dContactListener : public b2ContactListener {
 public:
  std::vector<b2Contact*> begin_contacts_;
  std::vector<b2Contact*> end_contacts_;

  void BeginContact(b2Contact* contact) override {
    if (contact->IsTouching()) begin_contacts_.push_back(contact);
  }

  void EndContact(b2Contact* contact) override {
    end_contacts_.push_back(contact);
  }
};

}

#endif //ENGINE_SRC_PHYSICS_ENGINE_SRC_PHYSICS_BOX2D_CONTACT_LISTENER_H_
