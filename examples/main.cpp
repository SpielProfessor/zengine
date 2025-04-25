#include "../include/zEngine.hpp"
#include <raylib.h>
//
// TESTING
//

class Player : public Sprite {
public:
  Player() : Sprite("TEX_TILESET") {
    setScale(3);
    position = Vector2{10, 10};
  }
  void fixedUpdate(float delta) override {
    if (IsKeyDown(KEY_A)) {
      position.x -= 10;
    } else if (IsKeyDown(KEY_D)) {
      position.x += 10;
    }
    if (IsKeyDown(KEY_W)) {
      position.y -= 10;
    } else if (IsKeyDown(KEY_S)) {
      position.y += 10;
    }
  }
};
class MainScene : public Scene {
public:
  MainScene() {
    backgroundColour = GREEN;
    updateInterval = 60;
    elements.push_back(NewUnique(Player));
  }
};
int main() {
  initializeTexture("TEX_TILESET", "set.png");
  EngineContext ctx("Hello there", 800, 450);
  ctx.setLetterbox(400, 225);
  ctx.switchTo<MainScene>();
  ctx.run();
}
