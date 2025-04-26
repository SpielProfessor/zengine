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
  // constructors with custom children
  Actor(std::vector<Unique(Actor)> children_)
      : children(std::move(children_)), position(Vector2{0, 0}),
        parent(nullptr), zindex(0) {}

  Actor(std::vector<Unique(Actor)> children_, int zindex_)
      : children(std::move(children_)), position(Vector2{0, 0}),
        parent(nullptr), zindex(zindex_) {}

  Actor(std::vector<Unique(Actor)> children_, Vector2 position_)
      : children(std::move(children_)), position(position_), parent(nullptr),
        zindex(0) {}

  Actor(std::vector<Unique(Actor)> children_, int zindex_, Vector2 position_)
      : children(std::move(children_)), position(position_), parent(nullptr),
        zindex(zindex_) {}
  // constructors without custom children
  Actor() : children(), position(Vector2{0, 0}), parent(nullptr), zindex(0) {}

  Actor(int zindex_)
      : children(), position(Vector2{0, 0}), parent(nullptr), zindex(zindex_) {}

  Actor(Vector2 position_)
      : children(), position(position_), parent(nullptr), zindex(0) {}

  Actor(int zindex_, Vector2 position_)
      : children(), position(position_), parent(nullptr), zindex(zindex_) {}

  // functions intended for overwriting
  // called when the actor is initialized
  virtual void initialize() {};
  // called every frame for drawing
  virtual void draw() {};
  // called a fixed number of times per frame
  virtual void fixedUpdate(float delta [[maybe_unused]]) {};
  // called every frame
  virtual void update(float delta [[maybe_unused]]) {};
  // background draw function; not intended to be overwritten, just extended
  virtual void _draw();
  // background update function; not intended to be overwritten, just extended
  virtual void _update(float delta);
  // background fixed update function; not intended to be overwritten, just
  // extended
  virtual void _fixedUpdate(float delta);
  // background initialization function; not intended to be overwritten, just
  // extended
  virtual void _initialize();
  // get the global position of the object
  Vector2 getGlobalPosition();
  // get the global X coordinate of the object
  float getGlobalX();
  // get the global Y coordinate of the object
  float getGlobalY();
  // add a child to the actor
  void addChild(Unique(Actor) child);
};
void sortActorsByZIndex(std::vector<Unique(Actor)> &elements);
