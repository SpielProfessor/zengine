#include "../include/zEngine.hpp"
#include <cstdio>
#include <raylib.h>
//
// TESTING
//
class Player : public AnimatedSprite {
private:
public:
  Player() : AnimatedSprite("TEX_TILESET") {
    position = Vector2{10, 10};
    // sprite->hflip = true;
    dimensions = Vector2{16.f, 16.f};
  }
  void initialize() override {
    AnimatedSpriteAnimation animation = AnimatedSpriteAnimation{
        .frameCount = 4,
        .frameWidth = 16,
        .frameHeight = 16,
        .animationRow = 0,
        .fps = 5.,

    };
    AnimatedSpriteAnimation secondary = AnimatedSpriteAnimation{
        .frameCount = 3,
        .frameWidth = 32,
        .frameHeight = 32,
        .animationRow = 16,
        .fps = 2.,

    };
    this->addAnimation("main", animation);
    this->addAnimation("secondary", secondary);
    this->switchTo("main");
  }
  void draw() override {}
  void update(float delta [[maybe_unused]]) override {
    if (IsKeyPressed(KEY_SPACE)) {
      if (this->paused) {
        this->play();
        printf("PLAYING!\n");
      } else {
        this->pause();
      }
    }
    if (IsKeyPressed(KEY_ONE)) {
      switchTo("main");
    }
    if (IsKeyPressed(KEY_TWO)) {
      switchTo("secondary");
    }
  }
};
class MainScene : public Scene {
public:
  MainScene() {
    backgroundColour = GREEN;
    updateInterval = 60;
    addActor(NewUnique(Player));
  }
};
int main() {
  SetTraceLogLevel(LOG_WARNING);
  initializeTexture("TEX_TILESET", "../set.png");

  EngineContext ctx("Hello there", 800, 450);
  ctx.setLetterbox(64, 64);
  ctx.switchTo<MainScene>();
  ctx.run();
}
