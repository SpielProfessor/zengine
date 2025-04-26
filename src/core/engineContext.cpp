#include "engineContext.hpp"
#include "raylib.h"
#include "texture.hpp"

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
      flags(flags_) {
  loadFlags();
}
void EngineContext::run() {
  // initialization
  InitWindow(width, height, title);
  loadTextures();
  float accumulator = 0.0f;
  currentScene->initialize();
  RenderTexture2D target = LoadRenderTexture(vWidth, vHeight);
  //  main loop
  while (running) {
    float delta = GetFrameTime();
    accumulator += delta;

    // logic
    if (WindowShouldClose()) {
      running = false;
    }
    currentScene->update(delta);
    // fixed update
    while (accumulator >= currentScene->getUpdateInterval()) {
      currentScene->fixedUpdate(delta);
      accumulator -= currentScene->getUpdateInterval();
    }

    // normal drawing
    if (!(flags & ENABLE_LETTERBOX)) {
      BeginDrawing();
      currentScene->draw();
      EndDrawing();
    }
    // letterboxed drawing
    else {
      // calculate scale
      float scale = MIN((float)GetScreenWidth() / vWidth,
                        (float)GetScreenHeight() / vHeight);

      // draw to a texture
      BeginTextureMode(target);
      currentScene->draw();
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
