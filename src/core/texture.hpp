#include <atomic>
#include <optional>
#include <raylib.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <unordered_map>
#pragma once

class TextureObject {
public:
  Texture texture = {0, 0, 0, 0, 0};
  bool built = false;
  std::string path;

  TextureObject(std::string path);
  TextureObject();
  ~TextureObject();
  void build();
  Texture2D getTexture();
};
void initializeTexture(std::string id, std::string path);
void loadTextures();
void unloadTextures();
void textureLoadingScreen();

extern std::unordered_map<std::string, TextureObject> TEXTURE_INDEX;
