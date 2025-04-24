#include "../actor/actor.hpp"
#include "core.hpp"
#include "vector"
#pragma once
//
// GAME WORLD
//
class Scene {
public:
  std::vector<Unique(Actor)> elements;
  int updateInterval;
  Color backgroundColour;

  Scene(int interval = 60);
  void initialize();
  virtual void update(float delta);
  virtual void fixedUpdate(float delta);
  virtual void draw();
  void setUpdateInterval(int interval = 60);
  float getUpdateInterval();
};
