#include "../include/zEngine.hpp"
#include <memory>
#include <raylib.h>
//
// TESTING
//
class Wall : public Collider {
public:
  Wall(int xTile, int yTile) {
    position = Vector2{(float)xTile * 16.f, (float)yTile * 16.f};
    dimensions = Vector2{16.f, 16.f};
  }
  void initialize() override {
    addChild(std::make_unique<Sprite>("TEX_TILESET",
                                      Rectangle{0., 16. * 0., 16., 16.}, 1));
  }
};

class Player : public Collider {
private:
public:
  Player() {
    position = Vector2{10, 10};
    // sprite->hflip = true;
    dimensions = Vector2{16.f, 16.f};
  }
  void initialize() override {
    addChild(std::make_unique<Sprite>(
        "TEX_TILESET", Rectangle{16. * 0., 16. * 0., 16., 16.}, 5));
  }
  void draw() override {
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 30, WHITE);
  }
  void fixedUpdate(float delta [[maybe_unused]]) override {
    if (IsKeyDown(KEY_A)) {
      this->move(Vector2{-5., 0.});
      // this->sprite->hflip = true;
    } else if (IsKeyDown(KEY_D)) {
      // this->sprite->hflip = false;
      this->move(Vector2{5., 0.});
    }
    if (IsKeyDown(KEY_W)) {

      this->move(Vector2{0., -5.});
    } else if (IsKeyDown(KEY_S)) {

      this->move(Vector2{0., 5.});
    }
  }
};
class MainScene : public Scene {
public:
  MainScene() {
    backgroundColour = GREEN;
    updateInterval = 60;
    addActor(NewUnique(Player));
    for (int i = 0; i < 100; i++) {
      addActor(std::make_unique<Wall>(i, 3));
    }
  }
};
int main() {
  SetTraceLogLevel(LOG_WARNING);
  initializeTexture("TEX_TILESET", "../set.png");

  EngineContext ctx("Hello there", 800, 450);
  addColliderDebugIntegration(&ctx);
  ctx.setLetterbox(400, 225);
  ctx.switchTo<MainScene>();

  ctx.run();
}
