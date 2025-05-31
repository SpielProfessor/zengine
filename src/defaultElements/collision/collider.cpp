#include "collider.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>
std::unordered_map<int, Collider *> COLLIDER_INDEX =
    std::unordered_map<int, Collider *>();
bool TO_CLEANUP_COLLIDERS = false;

void Collider::_initialize() {
  COLLIDER_INDEX.insert({this->getID(), this});
  Actor::_initialize();
}
Collider::~Collider() { COLLIDER_INDEX.erase(this->getID()); }
void Collider::move(Vector2 difference) {
  {
#ifdef _ZENGINE_COLLIDER_HARD_COLLISION
    Vector2 oldPos = position;
    position.x += difference.x;
    position.y += difference.y;
    CollisionShape *thisShape = findChildOfType<CollisionShape>();

    for (auto &collider : sceneLink->findElementsOfType<Collider>()) {
      if (collider->destroyed) {
        TO_CLEANUP_COLLIDERS = true;
        continue;
      }

      if (collider->getID() != this->getID()) {
        if (CheckCollisionRecs(collider->getSize(), thisShape->getSize())) {
          position = oldPos;
        }
      }
    }

#else
    Vector2 moveDir = vectorNormalize(difference); // Direction of movement
    float totalDist = vectorLength(difference);    // Distance to travel
    float stepSize = 1.0f; // Tune this for precision/performance
    float moved = 0.0f;

    //
    // ROUGH COLLISION DETECTION
    //
    //    std::unordered_map<int, Collider *> roughColliderIndex =
    //        std::unordered_map<int, Collider *>();
    std::vector<Rectangle> roughColliderIndex;

    // Check for collision
    Rectangle oldPositionRectangle = getSize()[0];
    Rectangle newPositionRectangle = oldPositionRectangle;
    newPositionRectangle.x += difference.x;
    newPositionRectangle.y += difference.y;

    Rectangle checkedRectangle = oldPositionRectangle;

    if (oldPositionRectangle.x <= newPositionRectangle.x) {
      checkedRectangle.width = newPositionRectangle.x - oldPositionRectangle.x +
                               oldPositionRectangle.width;
    } else {
      checkedRectangle.width = oldPositionRectangle.x - newPositionRectangle.x +
                               oldPositionRectangle.width;
      checkedRectangle.x = newPositionRectangle.x;
    }

    if (oldPositionRectangle.y <= newPositionRectangle.y) {
      checkedRectangle.height = newPositionRectangle.y -
                                oldPositionRectangle.y +
                                oldPositionRectangle.height;
    } else {
      checkedRectangle.height = oldPositionRectangle.y -
                                newPositionRectangle.y +
                                oldPositionRectangle.height;
      checkedRectangle.y = newPositionRectangle.y;
    }

    for (auto &pair : COLLIDER_INDEX) {
      Collider *collider = pair.second;
      if (collider->destroyed) {
        TO_CLEANUP_COLLIDERS = true;
        continue;
      }
      if (collider->getID() != this->getID()) {
        for (Rectangle coll : collider->getSize()) {
          if (CheckCollisionRecs(checkedRectangle, coll)) {
            roughColliderIndex.push_back(coll);
          }
        }
      }
    }

    // precise detection
    while (moved < totalDist) {
      float remaining = totalDist - moved;
      float thisStep = (remaining < stepSize) ? remaining : stepSize;
      position.x += moveDir.x * thisStep;
      position.y += moveDir.y * thisStep;
      moved += thisStep;

      // Check for collision
      for (auto &collider : roughColliderIndex) {
        if (CheckCollisionRecs(collider, getSize()[0])) {
          // Move back by one small step to the last safe position
          position.x -= moveDir.x * thisStep;
          position.y -= moveDir.y * thisStep;
          return;
        }
      }
    }
#endif
    if (TO_CLEANUP_COLLIDERS) {
      // remove actor

      for (auto it = COLLIDER_INDEX.begin(); it != COLLIDER_INDEX.end();) {
        if (it->second->destroyed) {
          it = COLLIDER_INDEX.erase(it); // erase returns the next iterator
        } else {
          ++it;
        }
      }

      TO_CLEANUP_COLLIDERS = false;
    }
  }
}
