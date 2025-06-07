#include "actor.hpp"
#include "../FEATURES.hpp"
#include "../core/core.hpp"
#include "../core/scene.hpp"
#include "algorithm"
#include <cstdio>
#include <raylib.h>
void Actor::_draw() {
  sortActorsByZIndexU(children);
  draw();
  // for (auto &child : children) {
  //   child->_draw();
  // }
}
void Actor::destroy() {
  this->destroyed = true;
  this->sceneLink->dirtyDelete = true;
}
void Actor::_fixedUpdate(float delta) {
  fixedUpdate(delta);
  for (auto &child : children) {
    child->_fixedUpdate(delta);
  }
}
void Actor::_update(float delta) {
  update(delta);
  for (auto &child : children) {
    child->_update(delta);
  }
}
void Actor::_initialize() {
#ifdef _ZENGINE_DEBUG_INIT
  if (!parent) {
    printf("|-initializing actor %d and children\n", getID());
  }
#endif
  initialized = true;
  initialize();
  for (auto &child : children) {
    child->_initialize();
#ifdef _ZENGINE_DEBUG_INIT
    printf("|->    initializing child %d\n", child->getID());
#endif
  }
}
Actor *Actor::addChild(Unique(Actor) child) {
  child->parent = this;
  child->sceneLink = sceneLink;
  Actor *raw = child.get();             // capture raw *before* moving
  children.push_back(std::move(child)); // move into children vector
  if (sceneLink) {
    sceneLink->allActors.push_back(raw);
  } else {
    puts("[ZENGINE::ERROR::ACTOR] sceneLink inaccessible");
  }
  if (initialized) {
    raw->_initialize();
  }
  return raw; // return raw pointer
}

Vector2 Actor::getGlobalPosition() {
  return Vector2{getGlobalX(), getGlobalY()};
}
float Actor::getGlobalX() {
  if (parent != nullptr) {
    return parent->getGlobalX() + position.x;
  } else {
    return position.x;
  }
}
float Actor::getGlobalY() {
  if (parent != nullptr) {
    return parent->getGlobalY() + position.y;
  } else {
    return position.y;
  }
}

void sortActorsByZIndexU(std::vector<Unique(Actor)> &elements) {
  std::sort(elements.begin(), elements.end(),
            [](const Unique(Actor) & a, const Unique(Actor) & b) {
              return a->zindex < b->zindex;
            });
}

void sortActorsByZIndex(std::vector<Actor *> &elements) {
  std::sort(
      elements.begin(), elements.end(),
      [](const Actor *a, const Actor *b) { return a->zindex < b->zindex; });
}
int Actor::nextID = 0;
