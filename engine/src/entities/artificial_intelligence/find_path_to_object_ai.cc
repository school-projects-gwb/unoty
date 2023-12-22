
#include <cmath>
#include <utility>
#include <queue>
#include <map>
#include <set>
#include <stack>

#include "entities/artificial_intelligence/find_path_to_object_ai.h"
#include "ai_base.h"
#include "a_star_path_node.h"

namespace engine::entities {

class FindPathToObjectAI::Impl : public AIBase {
 public:
  Impl() = default;
  ~Impl() override = default;

  bool FindPath() {
    target_reached_ = false;

    // A* Search Algorithm
    std::set<PathNode> open_list;

    Point size = this_->GetSize();
    Point half_size = this_->GetSize() / 2;

    std::map<float, std::map<float, std::pair<bool, double>>> visited_nodes;
    std::map<int, std::map<int, std::vector<std::shared_ptr<Transform>>>> invalid_tiles;
    std::map<int, std::map<int, std::vector<std::pair<std::shared_ptr<Transform>, int>>>> weighted_tiles;
    std::map<float, std::map<float, PathNode>> closed_list;

    // map out invalid tiles
    for (const auto& tag: invalid_tiles_) {
      auto objects = GameObject::GetSceneObjectsByTagName(tag);

      for (const auto& object: objects){
        auto transform = object->GetTransform();
        float max_x = transform->Position.x + (float)transform->GetSize().x + (float)size.x;
        float max_y = transform->Position.y + (float)transform->GetSize().y + (float)size.y;

        float cur_x = (transform->Position.x - (float)size.x);

        while(cur_x <= max_x){
          float cur_y = (transform->Position.y - (float)size.y);

          while(cur_y <= max_y){
            invalid_tiles[((int)cur_x / size.x)][((int)cur_y / size.y)].push_back(transform);

            cur_y += (float)size.y;
          }

          cur_x += (float)size.x;
        }
      }
    }

    //check if target isvalid
    auto in_it_x = invalid_tiles.find(((int)target_->Position.x / size.x));
    if (in_it_x != invalid_tiles.end()) {

      auto in_it_y = in_it_x->second.find(((int)target_->Position.y / size.y));
      if (in_it_y != in_it_x->second.end()) {
        //possible invalid tiles;
        for(const auto& tile : in_it_y->second){
          if(tile->IsOverlapping(target_)) {
            // target invalid
            path_ = std::stack<std::shared_ptr<Transform>>();
            target_reached_ = true;
            return false;
          }
        }
      }
    }

    // check if not already on target
    if (this_->IsInPositionBounds(target_->Position)) {
      path_ = std::stack<std::shared_ptr<Transform>>();
      path_.push(target_);
      return true;
    }

    // map out weighted tiles
    for (const auto& tag: objects_weights_) {
      auto objects = GameObject::GetSceneObjectsByTagName(tag.first);

      for (const auto& object: objects){
        auto transform = object->GetTransform();
        float max_x = transform->Position.x + (float)transform->GetSize().x + (float)size.x;
        float max_y = transform->Position.y + (float)transform->GetSize().y + (float)size.y;

        float cur_x = (transform->Position.x - (float)size.x);

        while(cur_x <= max_x){
          float cur_y = (transform->Position.y - (float)size.y);

          while(cur_y <= max_y){
            weighted_tiles[((int)cur_x / size.x)][((int)cur_y / size.y)].emplace_back(transform, tag.second);

            cur_y += (float)size.y;
          }

          cur_x += (float)size.x;
        }
      }
    }

    PathNode start;
    start.position_ = std::make_shared<Transform>();
    start.position_->Position = this_->Position;
    start.position_->SetSize(size);
    start.f_ = 0;
    start.g_ = 1;

    open_list.insert(start);
    visited_nodes[start.position_->Position.x][start.position_->Position.y] = {true, 0};

    while (!open_list.empty()) {
      auto q = *open_list.begin();
      open_list.erase(open_list.begin());

      Vector2d minus = q.position_->Position - half_size;
      Vector2d plus = q.position_->Position + half_size;
      bool left_in_range = false;
      bool top_in_range = false;
      bool right_in_range = false;
      bool bottom_in_range = false;
      std::vector<PathNode> successors;

      if ((float) top_left_border_.x < minus.x) {
        left_in_range = true;

        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position.x = minus.x;
        n.position_->Position.y = q.position_->Position.y;
        n.position_->SetSize(size);
        successors.push_back(n);
      }
      if ((float) top_left_border_.y < minus.y) {
        top_in_range = true;

        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position.x = q.position_->Position.x;
        n.position_->Position.y = minus.y;
        n.position_->SetSize(size);
        successors.push_back(n);
      }
      if ((float) bottom_right_border_.x > plus.x) {
        right_in_range = true;

        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position.x = plus.x;
        n.position_->Position.y = q.position_->Position.y;
        n.position_->SetSize(size);
        successors.push_back(n);
      }
      if ((float) bottom_right_border_.x > plus.x) {
        bottom_in_range = true;

        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position.x = q.position_->Position.x;
        n.position_->Position.y = plus.y;
        n.position_->SetSize(size);
        successors.push_back(n);
      }

      if (top_in_range && left_in_range) {
        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position = minus;
        n.position_->SetSize(size);
        successors.push_back(n);
      }
      if (top_in_range && right_in_range) {
        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position.x = plus.x;
        n.position_->Position.y = minus.y;
        n.position_->SetSize(size);
        successors.push_back(n);
      }
      if (bottom_in_range && left_in_range) {
        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position.x = minus.x;
        n.position_->Position.y = plus.y;
        n.position_->SetSize(size);
        successors.push_back(n);
      }
      if (bottom_in_range && right_in_range) {
        PathNode n;
        n.position_ = std::make_shared<Transform>();
        n.parent_ = q.position_;
        n.position_->Position = plus;
        n.position_->SetSize(size);
        successors.push_back(n);
      }

      for (auto p : successors) {
        auto c_it_x = closed_list.find(p.position_->Position.x);
        if (c_it_x != closed_list.end()) {

          auto c_it_y = c_it_x->second.find(p.position_->Position.y);
          if (c_it_y != c_it_x->second.end()) {
            //already processed;
            continue;
          }
        }

        // check if tile data exists
        double old_f = std::numeric_limits<double>::max();
        auto v_it_x = visited_nodes.find(p.position_->Position.x);
        if (v_it_x != visited_nodes.end()) {

          auto v_it_y = v_it_x->second.find(p.position_->Position.y);
          if (v_it_y != v_it_x->second.end()) {
            //already visited;
            if (!v_it_y->second.first) {
              // invalid tile
              continue;
            } else {
              old_f = v_it_y->second.second;
            }
          }
        }

        // check if tile is invalid
        in_it_x = invalid_tiles.find(((int)p.position_->Position.x / size.x));
        if (in_it_x != invalid_tiles.end()) {

          auto in_it_y = in_it_x->second.find(((int)p.position_->Position.y / size.y));
          if (in_it_y != in_it_x->second.end()) {
            //possible invalid tiles;
            bool invalid = false;
            for(const auto& tile : in_it_y->second){
              if(p.position_->IsOverlapping(tile)) {
                visited_nodes[p.position_->Position.x][p.position_->Position.y] = {false, 0};
                invalid = true;
                break;
              }
            }
            if(invalid){
              continue;
            }
          }
        }

        // check if tile is overlapping with target
        if (p.position_->IsOverlapping(target_)) {
          // path found
          closed_list[q.position_->Position.x][q.position_->Position.y] = q;
          StorePath(closed_list, p);

          return true;
        }

        int tile_weight = 1;
        // check if tile is weighted
        auto we_it_x = weighted_tiles.find(((int)p.position_->Position.x / size.x));
        if (we_it_x != weighted_tiles.end()) {

          auto we_it_y = we_it_x->second.find(((int)p.position_->Position.y / size.y));
          if (we_it_y != we_it_x->second.end()) {
            //possible weighted tiles;
            for(const auto& pair : we_it_y->second){
              if(p.position_->IsOverlapping(pair.first)) {
                tile_weight += pair.second;
              }
            }
          }
        }

        p.g_ = q.g_ + tile_weight;
        auto h = (double) std::sqrt(
            ((p.position_->Position.x - target_->Position.x) * (p.position_->Position.x - target_->Position.x))
                + ((p.position_->Position.y - target_->Position.y) * (p.position_->Position.y - target_->Position.y)));

        p.f_ = p.g_ + h;

        // skip if node was visited before and has a lower f
        if (old_f < p.f_) {
          continue;
        }

        open_list.insert(p);
        visited_nodes[p.position_->Position.x][p.position_->Position.y] = {true, p.f_};
      }
      closed_list[q.position_->Position.x][q.position_->Position.y] = q;
    }

    return false;
  }

  [[nodiscard]] std::shared_ptr<Transform> GetNewPosition() override {
    if (target_reached_ || path_.empty()) {
      return this_;
    }

    auto node = path_.top();

    float dx = node->Position.x - this_->Position.x;
    float dy = node->Position.y - this_->Position.y;

    position_->SetRotation(this_->GetRotation());
    position_->SetScale(this_->GetScale());

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= speed_) {
      // close enough to target
      path_.pop();

      if (path_.empty()) {
        target_reached_ = true;
      }

      position_->Position.x = node->Position.x;
      position_->Position.y = node->Position.y;
    } else {
      dx /= distance;
      dy /= distance;

      position_->Position.x = this_->Position.x + (dx * speed_);
      position_->Position.y = this_->Position.y + (dy * speed_);
    }

    return position_;
  }

  void SetTarget(std::shared_ptr<Transform> target) {
    target_ = std::move(target);
  }

  void StorePath(std::map<float, std::map<float, PathNode>> node_list, PathNode final) {
    path_ = std::stack<std::shared_ptr<Transform>>();
    path_.push(target_);

    while (final.parent_ != nullptr) {
      path_.push(final.position_);
      final = node_list[final.parent_->Position.x][final.parent_->Position.y];
    }
  }

  bool target_reached_ = true;
  float speed_ = 1.0f;
  std::vector<std::string> invalid_tiles_;
  std::vector<std::pair<std::string, int>> objects_weights_;
 private:
  std::shared_ptr<Transform> target_;
  std::stack<std::shared_ptr<Transform>> path_;

  Point top_left_border_{0, 0};
  Point bottom_right_border_{1000, 1000};
};

FindPathToObjectAI::~FindPathToObjectAI() = default;
FindPathToObjectAI::FindPathToObjectAI() : impl_(std::make_unique<Impl>()) {}

std::shared_ptr<Transform> FindPathToObjectAI::GetNewPosition() {
  return impl_->GetNewPosition();
}

void FindPathToObjectAI::Init(std::shared_ptr<Transform> target) {
  SetTarget(std::move(target));
  impl_->Init(this->GetGameObject().GetTransform());
}
void FindPathToObjectAI::SetTarget(std::shared_ptr<Transform> target) {
  impl_->SetTarget(std::move(target));
}
bool FindPathToObjectAI::FindPath() {
  return impl_->FindPath();
}

float FindPathToObjectAI::GetSpeed() {
  return impl_->speed_;
}
void FindPathToObjectAI::SetSpeed(float val) {
  impl_->speed_ = val;
}
bool FindPathToObjectAI::GetTargetReached() {
  return impl_->target_reached_;
}

void FindPathToObjectAI::AddInvalidTile(const std::string& tag) {
  impl_->invalid_tiles_.push_back(tag);
}
void FindPathToObjectAI::ClearInvalidTiles() {
  impl_->invalid_tiles_.clear();
}
void FindPathToObjectAI::RemoveInvalidTile(const std::string& tag) {
  impl_->invalid_tiles_.erase(std::remove(impl_->invalid_tiles_.begin(), impl_->invalid_tiles_.end(), tag), impl_->invalid_tiles_.end());
}

void FindPathToObjectAI::AddWeightedTile(const std::string& tag, int weight) {
  impl_->objects_weights_.emplace_back(tag, weight);
}
void FindPathToObjectAI::ClearWeightedTiles() {
  impl_->invalid_tiles_.clear();
}
void FindPathToObjectAI::RemoveWeightedTile(const std::string& tag) {
  impl_->invalid_tiles_.erase(std::remove(impl_->invalid_tiles_.begin(), impl_->invalid_tiles_.end(), tag), impl_->invalid_tiles_.end());
}
}