#pragma once
#include "engineContext.hpp"
#include "zDebug.hpp"
#include <cstdlib>
#include <raylib.h>

class ShowSizes : public DebugFeature {
public:
  ShowSizes() {
    command = "sizes";
    description = "Show/hide the size of objects";
  }
  bool enabled = false;
  int call(std::vector<std::string> arguments [[maybe_unused]],
           DebugManager *debugManager) override {
    enabled = !enabled;
    if (enabled) {
      debugManager->print("Showing sizes\n");
      debugManager->alwaysDraw = true;
    } else {
      debugManager->print("Hiding sizes\n");
    }
    return 0;
  }
  int draw(EngineContext *context) override {
    if (enabled) {
      for (auto &object : context->currentScene->allActors) {
        DrawRectangleLines(object->position.x, object->position.y,
                           object->dimensions.x, object->dimensions.y, WHITE);
      }
    }
    return 0;
  }
};
class ClearCommand : public DebugFeature {
public:
  ClearCommand() {
    command = "clear";
    description = "clears the debug console";
  }
  int call(std::vector<std::string> arguments [[maybe_unused]],
           DebugManager *debugManager [[maybe_unused]]) override {
    debugManager->output = "";
    return 0;
  }
};
class AlwaysDraw : public DebugFeature {
public:
  AlwaysDraw() {
    command = "ddaw";
    description = "always draw the debug overlay toggle";
  }
  int call(std::vector<std::string> arguments [[maybe_unused]],
           DebugManager *debugManager [[maybe_unused]]) override {
    if (!debugManager->alwaysDraw) {
      debugManager->print("always showing overlays\n");
      debugManager->alwaysDraw = true;
    } else {
      debugManager->print("only showing overlays when in debug menu\n");
      debugManager->alwaysDraw = false;
    }
    return 0;
  }
};
class ExitCommand : public DebugFeature {
public:
  ExitCommand() {
    command = "exit";
    description = "quit the entire application";
  }
  int call(std::vector<std::string> arguments [[maybe_unused]],
           DebugManager *debugManager [[maybe_unused]]) override {
    exit(0);
  }
};
void addDefaultDebugFeatures(DebugManager *manager);
