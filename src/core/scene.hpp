#pragma once
#include "../actor/actor.hpp"
#include "core.hpp"
#include "vector"
#include <algorithm>
#include <vector>
class EngineContext;

//
// GAME WORLD
//
class Scene {
public:
  // all actors
  std::vector<Unique(Actor)> elements;
  std::vector<Actor *> allActors;
  int updateInterval;
  bool initialized = false;
  bool dirtyDelete = true;
  Color backgroundColour;
  Rectangle screen = Rectangle{0., 0., 0., 0.};
  EngineContext *ctxLink;

  Scene(int interval = 60);
  void initialize();
  void addActor(Unique(Actor) actor);
  virtual void update(float delta);
  virtual void fixedUpdate(float delta);
  virtual void draw();
  virtual void drawHud();
  void deleteAllDestroyed() {
    // remove actor
    allActors.erase(
        std::remove_if(allActors.begin(), allActors.end(),
                       [](auto *actor) { return actor->destroyed; }),
        allActors.end());
  }
  void setUpdateInterval(int interval = 60);
  float getUpdateInterval();
  template <typename T> T *findElementOfType() {
    for (auto &element : elements) {
      if (T *casted = dynamic_cast<T *>(element.get())) {
        return casted;
      }
    }
    return nullptr;
  }
  template <typename T> std::vector<T *> findElementsOfType() {
    std::vector<T *> returned = std::vector<T *>();
    for (auto &element : elements) {
      if (T *casted = dynamic_cast<T *>(element.get())) {
        returned.push_back(casted);
      }
    }
    return returned;
  }
};
