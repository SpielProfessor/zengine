#include "../actor/actor.hpp"
#include "texture.hpp"
#include <string>
#pragma once
class Sprite : public Actor {
public:
  TextureHandle texture;
  float rotation = 0.0;
  float scale = 1.0;
  std::string path;
  Sprite(std::string path_) : path(path_) {}
  void _initialize() override;
  void _draw() override;
  void setScale(float scale);
  float getScale();
};
