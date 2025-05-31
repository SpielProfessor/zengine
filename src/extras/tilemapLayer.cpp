#include "tilemap.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
TileIndex loadTileIndex(const json &j, float tileSize);
void TileMapLayer::draw() {
  // draw a tilemap layer (optimized - based on the camera)
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
      drawTile(tilemap[y][x], x, y);
    }
  }
}

void TileMapLayer::drawTileTex(int x, int y, int tilesetX, int tilesetY) {
  DrawTexturePro(tileTexture->getTexture(),
                 // source
                 Rectangle{(float)tileSize * (float)tilesetX,
                           (float)tileSize * (float)tilesetY, (float)tileSize,
                           (float)tileSize},
                 // target
                 Rectangle{(float)x * (float)tileSize,
                           (float)y * (float)tileSize, (float)tileSize,
                           (float)tileSize},
                 Vector2{0., 0.}, 0., WHITE);
}

json loadJsonFile(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + path);
  }

  json j;
  file >> j; // Parses the JSON from the stream

  return j;
}
void TileMapLayer::loadFromJson(json file) {
  freeMap();
  width = file["width"];
  height = file["height"];
  tileSize = file["tilesize"];
  std::vector<int> tiles = file["tiles"].get<std::vector<int>>();
  tileTexture = &TEXTURE_INDEX[file["setname"]];
  tileTypes = loadTileIndex(file, tileSize);
  buildMap();
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      tilemap[y][x] = tiles.at(y * width + x);
    }
  }
}
void TileMapLayer::freeMap() {
  if (tilemap) {
    for (int i = 0; i < height; ++i) {
      delete[] tilemap[i];
    }
    delete[] tilemap;
  }
}
TileIndex loadTileIndex(const json &j, float tileSize) {
  TileIndex index;

  for (auto &[key, value] : j["tiletypes"].items()) {
    int tileID = std::stoi(key); // JSON keys are strings
    if (!value.is_array() || value.size() < 3)
      continue;

    float x = value[0];
    float y = value[1];

    TileParams params;
    params.size =
        Rectangle{x, y, tileSize, tileSize}; // assuming tileSizextileSize tiles
    params.isCollidable = value[2];          // or set this based on some rule

    index.tileIndex[tileID] = params;
  }

  return index;
}
