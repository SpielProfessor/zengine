#include "../actor/actor.hpp"
#include "../core/texture.hpp"
#include <raylib.h>
#include <string>
#pragma once
class Sprite : public Actor {
private:
  float rotation = 0.0;
  float scale = 1.0;
  Vector2 origin = {0., 0.};
  Color tint = WHITE;
  std::string textureIdent;
  TextureObject *textureLink = 0;
  Rectangle texturePart = Rectangle{0., 0., 0., 0.};

public:
  bool hflip = false;
  bool vflip = false;

  Sprite(std::string id) : textureIdent(id) {}
  Sprite(std::string id, Rectangle texturePart_)
      : textureIdent(id), texturePart(texturePart_) {}
  Sprite(std::string id, int zindex_) : textureIdent(id) { zindex = zindex_; }

  Sprite(std::string id, Rectangle texturePart_, int zindex_)
      : textureIdent(id), texturePart(texturePart_) {
    zindex = zindex_;
  }

  void _initialize() override;
  void _draw() override;
  void resetParams();
  // set the scale
  void setScale(float scale);
  // get the scale
  float getScale();

  // set the tint
  void setTint(Color color);
  // get the tint
  Color getTint();

  // set the rotation
  void setRotation(float rotation_);
  // get the rotation
  float getRotation();

  // change the texture
  void changeTexture(std::string identifier);
  // get the name of the current texture
  std::string getTextureName();
  // make the sprite only display a part of the texture
  void setTexturePart(Rectangle part);
  // get the current part of the display to be displayed
  Rectangle getTexturePart();
};
