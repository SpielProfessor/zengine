#include <raylib.h>
#include <string>
#pragma once
class TextureHandle {
public:
  Texture texture = {0};
  TextureHandle(std::string path);
  TextureHandle();
  ~TextureHandle();
};
