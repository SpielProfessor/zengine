#pragma once

#include <cmath>
#include <memory>
#include <raylib.h>

#define NewUnique(type) std::make_unique<type>()
#define Unique(type) std::unique_ptr<type>
#define Shared(type) std::shared_ptr<type>
#define NewShared(type) std::make_shared<type>()

// integer rectangle
struct RectangleI {
  int x;
  int y;
  int w;
  int h;
};
inline float vectorLength(Vector2 v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}

inline Vector2 vectorNormalize(Vector2 v) {
  float len = vectorLength(v);
  if (len == 0.0f)
    return {0.0f, 0.0f};
  return {v.x / len, v.y / len};
}

#define ZENGINE_VERSION "0.3a"
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__
