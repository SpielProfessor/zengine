#include "sprite.hpp"
#include <string>
#pragma once
typedef struct AnimatedSpriteAnimation {
  int frameCount;
  int frameWidth;
  int frameHeight;
  int animationRow;
  double fps;
} AnimatedSpriteAnimation;

class AnimatedSprite : public Sprite {
public:
  std::unordered_map<std::string, AnimatedSpriteAnimation> animations;
  AnimatedSpriteAnimation *currentAnimation = 0;
  int currentFrame = 0;
  double counter = 0.;
  bool paused = true;
  bool currentFrameChanged = true;
  // constructors
  AnimatedSprite(std::string id) : Sprite(id) {}
  AnimatedSprite(std::string id, std::string animationName,
                 AnimatedSpriteAnimation animation)
      : Sprite(id) {
    animations.insert({animationName, animation});
    currentAnimation = &animations["animationName"];
  }
  bool play() {
    if (!currentAnimation || !paused) {
      return false;
    }
    this->paused = false;
    return true;
  }
  bool pause() {
    if (!currentAnimation || paused) {
      return false;
    }
    this->paused = true;
    return true;
  }
  bool switchTo(std::string animationName) {
    if (animations.find(animationName) != animations.end()) {
      currentAnimation = &animations[animationName];
      currentFrame = 0;
      currentFrameChanged = true;
      return true;
    } else {
      return false;
    }
  }
  void _update(float delta) override {
    if (currentAnimation) {
      if (!paused) {
        counter += delta;
        if (counter > 1. / currentAnimation->fps) {
          counter -= 1. / currentAnimation->fps;
          currentFrame++;
          currentFrameChanged = true;
        }
        if (currentFrame >= currentAnimation->frameCount) {
          currentFrame = 0;
        }
      }
      if (currentFrameChanged) {
        setTexturePart(
            Rectangle{(float)currentAnimation->frameWidth * currentFrame,
                      (float)currentAnimation->animationRow,
                      (float)currentAnimation->frameWidth,
                      (float)currentAnimation->frameHeight});
        currentFrameChanged = false;
      }
    }
    this->update(delta);
  }
  void addAnimation(std::string animationName,
                    AnimatedSpriteAnimation animation) {
    animations.insert({animationName, animation});
  }
};
