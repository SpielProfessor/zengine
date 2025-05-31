#include "scene.hpp"
#include "../actor/actor.hpp"
#include "core.hpp"
#include "memory"
//
// WORLD
//

void Scene::update(float delta) {
  // Loop through each actor and update it
  for (auto &actor : elements) {
    actor->_update(delta);
  }
  if (this->dirtyDelete) {
    this->dirtyDelete = false;
    this->deleteAllDestroyed();
  }
}
void Scene::fixedUpdate(float delta) {
  for (auto &actor : elements) {
    actor->_fixedUpdate(delta);
  }
}
float Scene::getUpdateInterval() { return 1.0f / updateInterval; }
Scene::Scene(int interval)
    : updateInterval(interval), backgroundColour(BLACK) {}
void Scene::initialize() {

#ifdef _ZENGINE_DEBUG_INIT
  puts("|----------------------------------------------------------------|");
  puts("|   [ZENGINE::DEBUG::SCENE] beginning initialization of actors   |");
  puts("|----------------------------------------------------------------|");

#endif
  for (auto &actor : elements) {
    actor->_initialize();
  }
  initialized = true;
#ifdef _ZENGINE_DEBUG_INIT
  puts("|----------------------------------------------------------------|");
  puts("|[ZENGINE::DEBUG::SCENE] Finished initializing scenes and objects|");
  puts("|----------------------------------------------------------------|");
#endif
}
void Scene::addActor(Unique(Actor) actor) {
  actor->sceneLink = this;
  Actor *raw = actor.get();
  allActors.push_back(raw);
  elements.push_back(std::move(actor));
  if (initialized) {
    raw->_initialize();
  }
}
void Scene::drawHud() {}
void Scene::draw() {

  ClearBackground(backgroundColour);
  // Sort actors by zindex before drawing them
  sortActorsByZIndex(allActors);

  // Loop through each actor and draw it
  for (auto actor : allActors) {
    actor->_draw();
  }
}
void Scene::setUpdateInterval(int interval) { updateInterval = interval; }
