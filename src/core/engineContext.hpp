#include "core.hpp"
#include "scene.hpp"
#include "zDebug.hpp"
#include <raylib.h>
#pragma once
//
// ENGINE CONTEXT
//
typedef enum {
  FLAG_NONE = 0,
  CLOSE_ON_ESC = 1 << 0,
  ENABLE_LETTERBOX = 1 << 1,
  DISABLE_RESIZE = 1 << 2,
} EngineContextFlag;
// setup system for windows etc.
class EngineContext {
private:
  bool running = false;
  bool toSwitch = false;
  // initialize flags
  void loadFlags();

public:
  //
  // PROTOTYPE PROPERTIES
  //

  // the title of the prototype window
  char *title = (char *)"Nothing to see here";
  // the width of the prototype window
  int width = 800;
  // the height of the prototype window
  int height = 450;
  // the flags given to the window
  int flags = 0;
  // letterbox size
  int vWidth = 0;
  int vHeight = 0;

  // debug mode
  bool debugMode = false;
  DebugManager debugManager;

  // Camera

  Camera2D camera = {0, 0, 0, 0, 0, 0};
  //
  // RUNTIME ELEMENTS
  //
  Unique(Scene) currentScene;
  Unique(Scene) nextScene = 0;

  //
  // CONSTRUCTORS
  //

  // define the engine context and initialize the window prototype
  EngineContext(const char *title_, int width_, int height_, int flags_ = 0);
  //
  // METHODS
  //

  // start the main graphics loop of the application
  void run();
  void setLetterbox(int vWidth, int vHeight);
  void setFlag(EngineContextFlag flag);
  void unsetFlag(EngineContextFlag flag);
  template <typename T, typename... Args> void trySwitch(Args &&...args) {
    toSwitch = true;
    static_assert(std::is_base_of<Scene, T>::value, "T must be a Scene");
    nextScene = std::make_unique<T>(std::forward<Args>(args)...);
    nextScene->ctxLink = this;
  }
  template <typename T, typename... Args> void switchTo(Args &&...args) {
    static_assert(std::is_base_of<Scene, T>::value, "T must be a Scene");
    currentScene = std::make_unique<T>(std::forward<Args>(args)...);
    currentScene->ctxLink = this;
  }
};
