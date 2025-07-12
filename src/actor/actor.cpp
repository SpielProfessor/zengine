/********************************************
 * ACTOR.CPP                                *
 ********************************************
 * Standard functions for zengine actors.   *
 *                                          *
 * Copyright (C) SpielProfessor 2025.       *
 * Licensed under the 2-Clause BSD license  *
 ********************************************/
#include "actor.hpp"
#include "../core/core.hpp"
#include "../core/scene.hpp"
#include "algorithm"
#include <cstdio>
#include <raylib.h>

//
// IMPLEMENTATIONS OF ACTOR FUNCTIONS
//

// initialize the next ID used for an actor
int Actor::nextID = 0;

// backend drawing function for the actor
void Actor::_draw() {
  sortActorsByZIndexU(children);
  draw();
}
// destroy the actor and all its children
void Actor::destroy() {
  this->destroyed = true;
  this->sceneLink->dirtyDelete = true;
  for (auto &child : this->children) {
    child->destroy();
  }
  children.clear();
}
// backend fixed update for the actor, called as often as declared in the scene.
// also updates all children.
void Actor::_fixedUpdate(float delta) {
  fixedUpdate(delta);
  for (auto &child : children) {
    child->_fixedUpdate(delta);
  }
}

// backend update every frame; also updates all children
void Actor::_update(float delta) {
  update(delta);
  for (auto &child : children) {
    child->_update(delta);
  }
}

// backend initialization the actor
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

// add a child to the actor. Returns a reference to the child.
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

// get the position of the actor as a 2-dimensional vector, including offsets
// from parents.
Vector2 Actor::getGlobalPosition() {
  return Vector2{getGlobalX(), getGlobalY()};
}
// get the x-coordinate of the actor, including the offset from all parents.
float Actor::getGlobalX() {
  if (parent != nullptr) {
    return parent->getGlobalX() + position.x;
  } else {
    return position.x;
  }
}
// get the y-coordinate of the actor, including the offset from all parents.
float Actor::getGlobalY() {
  if (parent != nullptr) {
    return parent->getGlobalY() + position.y;
  } else {
    return position.y;
  }
}

// TODO:
// the following should be moved to another file

// helper function to sort a vector of unique actors
void sortActorsByZIndexU(std::vector<Unique(Actor)> &elements) {
  std::sort(elements.begin(), elements.end(),
            [](const Unique(Actor) & a, const Unique(Actor) & b) {
              return a->zindex < b->zindex;
            });
}
// helper function to sort a vector of actor pointers
void sortActorsByZIndex(std::vector<Actor *> &elements) {
  std::sort(
      elements.begin(), elements.end(),
      [](const Actor *a, const Actor *b) { return a->zindex < b->zindex; });
}
