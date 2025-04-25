#pragma once
// an actor that has the ability to draw and update
#include "../core/core.hpp"
#include <raylib.h>
#include <vector>
class Actor {
public:
  std::vector<Unique(Actor)> children;
  Vector2 position;
  Actor *parent = nullptr;
  int zindex;
  virtual void initialize() {};
  virtual void draw() {};
  virtual void fixedUpdate(float delta [[maybe_unused]]) {};
  virtual void update(float delta [[maybe_unused]]) {};
  // background draw function
  virtual void _draw();
  // background update function
  virtual void _update(float delta);
  // background fixed update function
  virtual void _fixedUpdate(float delta);
  virtual void _initialize();
  Vector2 getGlobalPosition();
  float getGlobalX();
  float getGlobalY();
  void addChild(Unique(Actor) child);
  Actor();
  Actor(int zindex_);
  Actor(Vector2 position_);
  Actor(int zindex_, Vector2 position_);
};
void sortActorsByZIndex(std::vector<Unique(Actor)> &elements);
