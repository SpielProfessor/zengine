#include "scene.hpp"
#include "../actor/actor.hpp"
#include "memory"
//
// WORLD
//

void Scene::update(float delta) {
  // Loop through each actor and update it
  for (auto &actor : elements) {
    actor->_update(delta);
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
  for (auto &actor : elements) {
    actor->_initialize();
  }
}

void Scene::draw() {

  ClearBackground(backgroundColour);
  // Sort actors by zindex before drawing them
  sortActorsByZIndex(elements);

  // Loop through each actor and draw it
  for (auto &actor : elements) {
    actor->_draw();
  }
}
void Scene::setUpdateInterval(int interval) { updateInterval = interval; }
