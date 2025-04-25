#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <vector>
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

extern std::unordered_map<std::string, TextureObject> TEXTURE_INDEX;
