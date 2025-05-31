#include "texture.hpp"
#include "../FEATURES.hpp"
#include <raylib.h>
#include <stdio.h>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, TextureObject> TEXTURE_INDEX;
TextureObject::TextureObject(std::string path_) : path(path_) {}
TextureObject::TextureObject() {}
TextureObject::~TextureObject() {}
void TextureObject::build() {
  built = true;
  texture = LoadTexture(path.c_str());
}
Texture2D TextureObject::getTexture() {
  if (!built) {
    puts("[WARNING] cannot get a unbuilt texture");
  }
  return texture;
}
void unloadTextures() {
#ifdef _ZENGINE_DEBUG
  puts("Unloading assets");
#endif
  // unload everything
  for (auto pair : TEXTURE_INDEX) {
    if (IsTextureValid(pair.second.texture)) {
      UnloadTexture(pair.second.texture);
    }
  }
}

void initializeTexture(std::string id, std::string path) {
  TEXTURE_INDEX[id] = TextureObject(path);
}
void loadTextures() {
#ifdef _ZENGINE_DEBUG
  puts("Loading assets");
#endif
  for (auto &pair : TEXTURE_INDEX) {
    pair.second.build();
  }
#ifdef _ZENGINE_DEBUG
  puts("Finished loading assets");
#endif
}

void textureLoadingScreen() {
  // draw loading screen
#ifdef LOADING_SCREEN_FN
  LOADING_SCREEN_FN();
#else

  BeginDrawing();
  {
    int fontSize = 20;
    const char *draw = "zengine";
    DrawText("ZEngine", GetScreenWidth() / 2 - MeasureText(draw, fontSize) / 2,
             GetScreenHeight() - fontSize - 20, fontSize, WHITE);
  }
  EndDrawing();
#endif
}
