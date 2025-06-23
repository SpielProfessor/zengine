#include "../../core/engineContext.hpp"
#include "../../core/zDebug.hpp"
#include "collider.hpp"
#include <raylib.h>
#pragma once
void addColliderDebugIntegration(EngineContext *ctx);

class ColliderDebug : public DebugFeature {
public:
  bool enabled = false;
  ColliderDebug() {
    this->command = "vcol";
    this->description = "show the colliders";
  }
  int call(std::vector<std::string> arguments,
           DebugManager *debugManager) override {
    enabled = !enabled;
    if (enabled) {
      debugManager->print("Showing colliders\n");
      debugManager->alwaysDraw = true;
    } else {
      debugManager->print("Hiding colliders\n");
    }
    return 0;
  }
  int draw(EngineContext *context) override {
    if (enabled) {
      for (auto &object : COLLIDER_INDEX) {
        for (auto &rect : object.second->getSize()) {
          DrawRectangleLinesEx(rect, 2, RED);
        }
      }
    }
    return 0;
  }
};
