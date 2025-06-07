#include "../../include/zEngine.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
using json = nlohmann::json;
#pragma once

json loadJsonFile(const std::string &path);
typedef struct TileParams {
  Rectangle size;
  bool isCollidable;
} TileParams;
class TileIndex {
public:
  std::unordered_map<int, TileParams> tileIndex;
  TileIndex() : tileIndex() {}
  TileIndex(std::unordered_map<int, TileParams> index) : tileIndex(index) {}
};
class TileMapLayer : public Collider {
public:
  TileIndex tileTypes = TileIndex();
  int **tilemap = 0;
  int width, height = 0;
  int screenWidth, screenHeight = 0;
  int tileSize = 0;
  TextureObject *tileTexture = 0;
  TileMapLayer(int zindex_, int width_, int height_, int screenWidth_,
               int screenHeight_, int tileSize_, TextureObject *tileset)
      : tileTypes(), width(width_), height(height_), screenWidth(screenWidth_),
        screenHeight(screenHeight_), tileSize(tileSize_), tileTexture(tileset) {
    zindex = zindex_;
    buildMap();
  }
  TileMapLayer(json jsonLayerFile) { this->loadFromJson(jsonLayerFile); }
  void buildMap() {
    this->tilemap = new int *[height];
    for (int y = 0; y < height; y++) {
      tilemap[y] = new int[width];
      for (int x = 0; x < width; x++) {
        tilemap[y][x] = 0;
      }
    }
  }
  void setTileIndex(std::unordered_map<int, TileParams> tileIndex_) {
    tileTypes = TileIndex(tileIndex_);
  }
  void setTileIndex(TileIndex tiles) { tileTypes = tiles; }
  void draw() override;
  virtual void drawTile(int tile, int x, int y) {
    drawTileTex(x, y, tileTypes.tileIndex[tile].size.x,
                tileTypes.tileIndex[tile].size.y);
  }
  void drawTileTex(int x, int y, int tilesetX, int tilesetY);
  void loadFromJson(json json);
  void freeMap();

  void populate(int tile) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        tilemap[y][x] = tile;
      }
    }
  }
  std::vector<Rectangle> getSize() override {
    std::vector<Rectangle> returned;

    // get collision based on the screen
    int startY, startX, endY, endX;
    int tileX = this->sceneLink->ctxLink->camera.target.x / tileSize;
    int tileY = this->sceneLink->ctxLink->camera.target.y / tileSize;
    int screen_h = (float)screenHeight / this->sceneLink->ctxLink->camera.zoom;
    int screen_w = (float)screenWidth / this->sceneLink->ctxLink->camera.zoom;

    // -1 and +3 for padding
    startY = tileY;
    startX = tileX;
    endY = startY + (screen_h) / tileSize + 3;
    endX = startX + (screen_w) / tileSize + 3;

    if (endX > width) {
      endX -= endX - width;
    }
    if (endY > height) {
      endY -= endY - height;
    }
    if (startX < 0) {
      startX = 0;
    }
    if (startY < 0) {
      startY = 0;
    }

    for (int y = startY; y < endY; y++) {
      for (int x = startX; x < endX; x++) {
        if (tileTypes.tileIndex[tilemap[y][x]].isCollidable) {
          returned.push_back(Rectangle{(float)x * tileSize, (float)y * tileSize,
                                       (float)tileSize, (float)tileSize});
        }
      }
    }

    return returned;
  }
};

void drawTileTex(int x, int y, int tilesetX, int tilesetY);
TileIndex loadTileIndex(const json &j, float tileSize);
