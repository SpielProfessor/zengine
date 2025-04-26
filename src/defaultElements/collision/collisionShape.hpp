#include "../../actor/actor.hpp"
#include <raylib.h>
class CollisionShape : public Actor {
public:
  Vector2 size;
  CollisionShape(Vector2 size_) : size(size_) {}
  CollisionShape(Vector2 position_, Vector2 size_) : size(size_) {
    position = position_;
  }
};
