#pragma once
// an actor that has the ability to draw and update
#include "../core/core.hpp"
#include <raylib.h>
#include <vector>

class Scene;
class Actor {
public:
  std::vector<Unique(Actor)> children;

  Vector2 position;
  Vector2 dimensions;
  Actor *parent = nullptr;
  Scene *sceneLink = nullptr;
  int zindex;
  bool destroyed;
  // constructors with custom children
  Actor(std::vector<Unique(Actor)> children_)
      : children(std::move(children_)), position(Vector2{0, 0}),
        parent(nullptr), zindex(0), id(generateID()) {}

  Actor(std::vector<Unique(Actor)> children_, int zindex_)
      : children(std::move(children_)), position(Vector2{0, 0}),
        parent(nullptr), zindex(zindex_), id(generateID()) {}

  Actor(std::vector<Unique(Actor)> children_, Vector2 position_)
      : children(std::move(children_)), position(position_), parent(nullptr),
        zindex(0), id(generateID()) {}

  Actor(std::vector<Unique(Actor)> children_, int zindex_, Vector2 position_)
      : children(std::move(children_)), position(position_), parent(nullptr),
        zindex(zindex_), id(generateID()) {}
  // constructors without custom children
  Actor()
      : children(), position(Vector2{0, 0}), parent(nullptr), zindex(0),
        id(generateID()) {}

  Actor(int zindex_)
      : children(), position(Vector2{0, 0}), parent(nullptr), zindex(zindex_),
        id(generateID()) {}

  Actor(Vector2 position_)
      : children(), position(position_), parent(nullptr), zindex(0),
        id(generateID()) {}

  Actor(int zindex_, Vector2 position_)
      : children(), position(position_), parent(nullptr), zindex(zindex_),
        id(generateID()) {}
  void destroy();

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
  Actor *addChild(Unique(Actor) child);
  template <typename T> T *findChildOfType() {
    for (auto &child : children) {
      if (T *casted = dynamic_cast<T *>(child.get())) {
        return casted;
      }
    }
    return nullptr;
  }
  int getID() const { return id; }

private:
  static int nextID; // Static variable to generate unique IDs
  int id;
  int value;

  static int generateID() { return nextID++; }
};

void sortActorsByZIndexU(std::vector<Unique(Actor)> &elements);
void sortActorsByZIndex(std::vector<Actor *> &elements);
