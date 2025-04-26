#include "sprite.hpp"
#include "../core/texture.hpp"
#include <raylib.h>
#include <string>
void Sprite::_initialize() {
  Actor::_initialize();
  textureLink = &TEXTURE_INDEX[textureIdent];
}
void Sprite::_draw() {
  Actor::_draw();
  DrawTexture(textureLink->getTexture(), getGlobalX(), getGlobalY(), WHITE);
}
void Sprite::setScale(float scale_) { scale = scale_; }
float Sprite::getScale() { return scale; }
