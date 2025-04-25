#include "sprite.hpp"
#include "texture.hpp"
#include <raylib.h>
#include <string>
void Sprite::_initialize() { Actor::_initialize(); }
void Sprite::_draw() {
  Actor::_draw();
  DrawTexture(TEXTURE_INDEX[textureIdent].texture, 0, 0, WHITE);
}
void Sprite::setScale(float scale_) { scale = scale_; }
float Sprite::getScale() { return scale; }
