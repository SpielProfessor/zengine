#include "../include/extras.hpp"
#include "../include/zEngine.hpp"
#include <memory>
#include <raylib.h>
//
// TESTING
//
class TileMap : public TileMapLayer {
public:
  TileMap()
      : TileMapLayer(0, 100, 100, 400, 225, 16, &TEXTURE_INDEX["TEX_TILESET"]) {
    std::unordered_map<int, TileParams> index;
    setTileIndex(index);
    loadFromJson(loadJsonFile("../example.json"));
  }
};

class Player : public Collider {
private:
  Sprite *sprite = 0;

public:
  Player() {
    position = Vector2{10, 10};
    // sprite->hflip = true;
    dimensions = Vector2{16.f, 16.f};
  }
  void initialize() override {
    sprite = (Sprite *)addChild(std::make_unique<Sprite>(
        "TEX_TILESET", Rectangle{16. * 0., 16. * 7., 16., 16.}, 5));
  }
  void draw() override {
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 30, WHITE);
  }
  void fixedUpdate(float delta [[maybe_unused]]) override {
    if (IsKeyDown(KEY_A)) {
      this->move(Vector2{-5., 0.});
      if (sprite) {
        this->sprite->hflip = true;
      }
    } else if (IsKeyDown(KEY_D)) {
      if (sprite) {
        this->sprite->hflip = false;
      }
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
    addActor(std::make_unique<TileMap>());
  }
};
int main() {
  SetTraceLogLevel(LOG_WARNING);
  initializeTexture("TEX_TILESET", "../set.png");

  EngineContext ctx("Hello there", 800, 450);
  ctx.setLetterbox(400, 225);
  ctx.switchTo<MainScene>();
  ctx.run();
}
