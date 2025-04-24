#include "../include/zEngine.hpp"
#include <raylib.h>
//
// TESTING
//
class Circle : public Actor {
public:
  Circle() { position = Vector2{10, 10}; }
  void draw() override {
    DrawCircle((int)getGlobalX(), (int)getGlobalY(), 20, WHITE);
  }
};

class Player : public Sprite {
public:
  Player() : Sprite("assets/forest.png") {
    setScale(3);
    position = Vector2{10, 10};
    addChild(NewUnique(Circle));
  }
  void draw() override {
    DrawRectangle((int)getGlobalX(), (int)getGlobalY(), 70, 80, WHITE);
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
  EngineContext ctx("Hello there", 800, 450);
  ctx.setLetterbox(400, 225);
  ctx.currentScene = new MainScene;
  ctx.run();
}
