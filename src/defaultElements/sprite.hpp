#include "../actor/actor.hpp"
#include "texture.hpp"
#include <string>
#pragma once
class Sprite : public Actor {
public:
  float rotation = 0.0;
  float scale = 1.0;
  std::string textureIdent;
  Sprite(std::string id) : textureIdent(id) {}
  void _initialize() override;
  void _draw() override;
  void setScale(float scale);
  float getScale();
};
