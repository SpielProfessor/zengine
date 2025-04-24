#include "sprite.hpp"
#include <raylib.h>
#include <string>
void Sprite::_initialize() {
  Actor::_initialize();
  texture.texture = LoadTexture(path.c_str());
}
void Sprite::_draw() {
  Actor::_draw();
  DrawTextureEx(texture.texture, getGlobalPosition(), rotation, scale, WHITE);
}
void Sprite::setScale(float scale_) { scale = scale_; }
float Sprite::getScale() { return scale; }
