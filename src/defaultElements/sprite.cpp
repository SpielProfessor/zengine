#include "sprite.hpp"
#include "../FEATURES.hpp"
#include "../core/scene.hpp"
#include "../core/texture.hpp"
#include <cstdio>
#include <iostream>
#include <raylib.h>
#include <string>
void Sprite::_initialize() {
  Actor::_initialize();

  changeTexture(textureIdent);
#ifdef _ZENGINE_DEBUG_INIT
  std::cout << "[DEBUG] changing texture to " << textureIdent << std::endl;
#endif
}
void Sprite::_draw() {
  Actor::_draw();

  Texture2D *tex = &textureLink->texture;
  // on-screen destination
  Rectangle dest = {getGlobalX(), getGlobalY(), texturePart.width * scale,
                    texturePart.height * scale};
  Rectangle source = this->texturePart;
  // full texture
  if (texturePart.x == 0. && texturePart.y == 0. && texturePart.width == 0. &&
      texturePart.height == 0.) {
    source = Rectangle{0., 0., (float)tex->width, (float)tex->height};
    dest = {getGlobalX(), getGlobalY(), tex->width * scale,
            tex->height * scale};
  }

  if (hflip) {
    source.width = -source.width;
  }

  if (vflip) {
    source.height = -source.height;
  }

  if (!tex) {
    puts("\n-----[ENGINE ERROR]-----");
    puts("[ERROR]: invalid texture\nin class `Sprite`\n->in method \
    `_draw`:");
    std::cout << "Tried using texture " + textureIdent + " but \
    pointer was "
              << textureLink << " (invalid)" << std::endl;
    printf("-> zEngine OID: %d\n", getID());
    puts("-----[END OF ERROR]-----");
    puts("FATAL ERROR OCCURED - EXITING FORCEFULLY");
  } else {
    DrawTexturePro(*tex, source, dest, origin, rotation, tint);
  }
}
void Sprite::setScale(float scale_) { scale = scale_; }
float Sprite::getScale() { return scale; }

// set the tint
void Sprite::setTint(Color color) { tint = color; }
// get the tint
Color Sprite::getTint() { return tint; }

// set the rotation
void Sprite::setRotation(float rotation_) { rotation = rotation_; }
// get the rotation
float Sprite::getRotation() { return rotation; }

// change the texture
void Sprite::changeTexture(std::string identifier) {
  textureIdent = identifier;
  textureLink = &TEXTURE_INDEX[identifier];
  // Texture2D *tex = &textureLink->texture;

  // on-screen destination
  //  Rectangle dest = {getGlobalX(), getGlobalY(), (float)tex->width * scale,
  //                    (float)tex->height * scale};
}
void Sprite::resetParams() {
  texturePart = {
      0.f,
      0.f,
      (float)textureLink->texture.width,
      (float)textureLink->texture.height,
  };
  origin = {0.f, 0.f};
  scale = 1.0;
  rotation = 0.f;
  tint = WHITE;
}
// get the name of the current texture
std::string Sprite::getTextureName() { return textureIdent; }
// make the sprite only display a part of the texture
void Sprite::setTexturePart(Rectangle part) { texturePart = part; }
// get the current part of the display to be displayed
Rectangle Sprite::getTexturePart() { return texturePart; }
