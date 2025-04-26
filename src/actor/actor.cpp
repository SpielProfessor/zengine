#include "actor.hpp"
#include "../core/core.hpp"
#include "algorithm"
#include <raylib.h>
void Actor::_draw() {
  sortActorsByZIndex(children);
  draw();
  for (auto &child : children) {
    child->_draw();
  }
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
void Actor::_initialize() { initialize(); }
void Actor::addChild(Unique(Actor) child) {
  child->parent = this;
  children.push_back(std::move(child));
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

void sortActorsByZIndex(std::vector<Unique(Actor)> &elements) {
  std::sort(elements.begin(), elements.end(),
            [](const Unique(Actor) & a, const Unique(Actor) & b) {
              return a->zindex < b->zindex;
            });
}
