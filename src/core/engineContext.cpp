#include "engineContext.hpp"
#include "../FEATURES.hpp"
#include "core.hpp"
#include "raylib.h"
#include "texture.hpp"
#include "zDebug.hpp"
#include <cstdio>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

//
// ENGINE CONTEXT
//

void EngineContext::loadFlags() {
  if (flags & CLOSE_ON_ESC) {
    // do nothing; raylib default
  } else {
    SetExitKey(KEY_NULL);
  }
}
EngineContext::EngineContext(const char *title_, int width_, int height_,
                             int flags_)
    : running(true), title((char *)title_), width(width_), height(height_),
      flags(flags_), debugManager() {
  printf("------ ZEngine version %s ------\n", ZENGINE_VERSION);
  printf("Built on %s at %s\n", BUILD_DATE, BUILD_TIME);
  printf("\nCompile-time features:\n");
#ifdef _ZENGINE_DEBUG
  puts("  - debug mode");
#endif
#ifdef _ZENGINE_DEBUG_INIT
  puts("  - initialization debugging");
#endif
  printf("--------------------------------\n");
#ifdef _ZENGINE_DEBUG
  puts("[ZENGINE::DEBUG::EngineContext] builiding EngineContext");
#endif
  camera.target = (Vector2){0., 0.};
  camera.offset = (Vector2){(float)GetScreenWidth(), (float)GetScreenHeight()};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  loadFlags();
}
void EngineContext::run() {
  // begin execution
#ifdef _ZENGINE_DEBUG
  puts("[ZENGINE::DEBUG::EngineContext] starting EngineContext running");
#endif
  // load flags
  // TODO: make resizability configurable
  if (!(flags & DISABLE_RESIZE)) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  }
  // initialization
  // initialize window
  InitWindow(width, height, title);
  // load textures

  textureLoadingScreen();
  loadTextures();

  // begin actual initialization and loading
  float accumulator = 0.0f;
  currentScene->screen = Rectangle{0., 0., (float)vWidth, (float)vHeight};
  currentScene->initialize();
  RenderTexture2D target = LoadRenderTexture(vWidth, vHeight);
#ifdef _ZENGINE_DEBUG
  puts("[ZENGINE::DEBUG::EngineContext] initialization complete. beginning "
       "main game loop...");
#endif
  //  main loop
  while (running) {
    float delta = GetFrameTime();
    accumulator += delta;

    // logic
    if (WindowShouldClose()) {
      running = false;
    }
    //
    // DEBUG MODE
    //
    if (IsKeyPressed(KEY_F3)) {
      this->debugMode = !this->debugMode;
    }
    if (this->debugMode) {
      this->debugManager.update();
    } else {
      currentScene->update(delta);
      // fixed update (if not in debug mode)
      while (accumulator >= currentScene->getUpdateInterval()) {
        currentScene->fixedUpdate(delta);
        accumulator -= currentScene->getUpdateInterval();
      }
    }

    // normal drawing
    if (!(flags & ENABLE_LETTERBOX)) {
      BeginDrawing();
      {
        BeginMode2D(camera);
        currentScene->draw();
        EndMode2D();
      }

      EndDrawing();
    }
    // letterboxed drawing
    else {
      // calculate scale
      float scale = MIN((float)GetScreenWidth() / vWidth,
                        (float)GetScreenHeight() / vHeight);

      // draw to a texture
      BeginTextureMode(target);
      {
        // camera-drawn
        BeginMode2D(camera);
        currentScene->draw();
        EndMode2D();
        // HUD
        currentScene->drawHud();
      }
      EndTextureMode();

      BeginDrawing();
      ClearBackground(BLACK); // Clear screen background

      // Draw render texture to screen, properly scaled
      DrawTexturePro(
          target.texture,
          (Rectangle){0.0f, 0.0f, (float)target.texture.width,
                      (float)-target.texture.height},
          (Rectangle){(GetScreenWidth() - ((float)vWidth * scale)) * 0.5f,
                      (GetScreenHeight() - ((float)vHeight * scale)) * 0.5f,
                      (float)vWidth * scale, (float)vHeight * scale},
          (Vector2){0, 0}, 0.0f, WHITE);
      if (this->debugMode) {
        debugManager.draw();
      }
      EndDrawing();
    }
  }
  // cleanup
  UnloadRenderTexture(target);
  unloadTextures();
  CloseWindow();
}
void EngineContext::setLetterbox(int vWidth_, int vHeight_) {
  vWidth = vWidth_;
  vHeight = vHeight_;
  setFlag(ENABLE_LETTERBOX);
}
void EngineContext::setFlag(EngineContextFlag flag) { flags = flags | flag; }
void EngineContext::unsetFlag(EngineContextFlag flag) { flags = flags & ~flag; }
