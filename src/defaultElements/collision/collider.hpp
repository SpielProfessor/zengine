#include "../../actor/actor.hpp"
#include <raylib.h>
#include <unordered_map>
#include <vector>
#pragma once
class Collider : public Actor {
public:
  void _initialize() override;
  void _fixedUpdate(float delta) override { Actor::_fixedUpdate(delta); }

  virtual std::vector<Rectangle> getSize() {
    return {Rectangle{getGlobalX(), getGlobalY(), dimensions.x, dimensions.y}};
  }
  void move(Vector2 difference);
  ~Collider();
};

extern std::unordered_map<int, Collider *> COLLIDER_INDEX;
