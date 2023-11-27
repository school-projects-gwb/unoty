#ifndef SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_DRAG_HANDLER_H_
#define SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_DRAG_HANDLER_H_

#include "iostream"
#include "entities/listeners/mouse_listener.h"
#include "entities/behaviour_script.h"
#include "draggable_object.h"
#include "entities/structs/input.h"
#include "entities/sprite.h"

using namespace engine::entities;

namespace slime_shooter {

class DragHandler : public MouseListener {
 public:
  void OnMousePressed() override {
    if (!objects_initialised_) InitObjects();

    for (const auto& object : draggable_objects_) {
      if (!object->GetTransform()->IsInPositionBounds(GetMousePositionWithOffset())) continue;

      drag_object_ = object;
      drag_object_sprite_ = drag_object_->GetComponentByType<Sprite>();
      drag_object_sprite_->SetColor({0, 255, 0});
      initial_drag_object_position_ = drag_object_->GetTransform()->Position;
      is_drag_active_ = true;
      break;
    }
  }

  void OnMouseMoved() override {
    if (!is_drag_active_) return;

    drag_object_->GetTransform()->Position = GetMousePositionWithOffset();
    drag_object_sprite_->SetColor(IsCurrentDragObjectInGamePositionBounds() ? Color{0,255,0} : Color{255, 0, 0});
  }

  void OnMouseReleased() override {
    if (!is_drag_active_) return;
    if (!objects_initialised_) InitObjects();

    if (!IsCurrentDragObjectInGamePositionBounds()) drag_object_->GetTransform()->Position = initial_drag_object_position_;
    drag_object_sprite_->SetColor({255, 255, 255});
    drag_object_sprite_ = nullptr;
    is_drag_active_ = false;
    drag_object_ = nullptr;
  }

 private:
  std::vector<std::shared_ptr<DraggableObject>> draggable_objects_;
  bool objects_initialised_ = false;
  bool is_drag_active_ = false;
  Vector2d initial_drag_object_position_;
  std::shared_ptr<Sprite> drag_object_sprite_ = nullptr;
  std::shared_ptr<DraggableObject> drag_object_ = nullptr;

  int min_x = 40, max_x = 550, min_y = 55, max_y = 450;
  int mouse_position_offset_ = 32;

  [[nodiscard]] Vector2d GetMousePositionWithOffset() const {
  auto mouse_position = Input::GetMousePointerPosition();
  return {mouse_position.x - mouse_position_offset_, mouse_position.y - mouse_position_offset_};
  }

  void InitObjects() {
    objects_initialised_ = true;
    auto draggable_objects = GameObject::GetSceneObjectsByTagName("draggable_object");
    for (const auto& draggable_object : draggable_objects)
      draggable_objects_.emplace_back(GameObject::Cast<DraggableObject>(draggable_object));
  }

  bool IsCurrentDragObjectInGamePositionBounds() {
    auto check_pos = drag_object_->GetTransform()->Position;
    bool in_bounds_x = check_pos.x >= min_x && check_pos.x <= max_x;
    bool in_bounds_y = check_pos.y >= min_y && check_pos.y <= max_y;

    return in_bounds_x && in_bounds_y;
  }
};

}

#endif //SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_SLIME_SHOOTER_SRC_UI_LEVEL_EDITOR_EDITOR_OBJECTS_DRAG_HANDLER_H_
