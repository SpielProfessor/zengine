#include "../actor/actor.hpp"
#include "tilemapLayer.hpp"
#include <memory>
#include <utility>
#include <vector>
#pragma once
// a tilemap layer in a json file
struct Layer {
  int width;
  int height;
  std::vector<int> tiles;
};
// helper function for json library to allow struct `Layer` to be deserialized
void from_json(const json &j, Layer &layer);
// a tilemap
class Tilemap : public Actor {
  std::vector<TileMapLayer *> layers = std::vector<TileMapLayer *>();
  int screenWidth = 0;
  int screenHeight = 0;

public:
  Tilemap() {}
  Tilemap(int screenWidth_, int screenHeight_)
      : screenWidth(screenWidth_), screenHeight(screenHeight_) {}
  // load a tilemap from json
  void loadFile(json file) {
    int tileSize = file["tilesize"];
    TextureObject *tileTexture = &TEXTURE_INDEX[file["setname"]];
    TileIndex tileTypes = loadTileIndex(file, tileSize);
    std::unordered_map<int, Layer> layers;
    for (auto &[key, value] : file["layers"].items()) {
      layers[atoi(key.c_str())] = value.get<Layer>();
    }
    for (auto &[key, value] : layers) {
      std::unique_ptr<TileMapLayer> l = std::make_unique<TileMapLayer>(
          key, value.width, value.height, this->screenWidth, this->screenHeight,
          tileSize, tileTexture);
      l->setTileIndex(tileTypes);
      l->buildMap();
      // add tiles
      for (int y = 0; y < value.height; y++) {
        for (int x = 0; x < value.width; x++) {
          l->tilemap[y][x] = value.tiles.at(y * value.width + x);
        }
      }
      addLayer(std::move(l));
    }
  }
  // add a layer
  void addLayer(std::unique_ptr<TileMapLayer> newLayer) {
    TileMapLayer *layer = (TileMapLayer *)addChild(std::move(newLayer));
    this->layers.push_back(layer);
  }
  // gets the highest tile at a specific position. Returns -1 if the tile there
  // is out of bounds.
  int getTopTile(int x, int y) {
    if (x < 0 || y < 0) {
      return -1;
    }
    int tile = -1;
    for (int i = layers.size() - 1; i >= 0; i--) {
      if (x < layers[i]->width && y < layers[i]->height) {
        tile = layers[i]->tilemap[y][x];
      }
    }
    return tile;
  }
};
