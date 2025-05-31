#include "tilemap.hpp"
// helper function for json library to allow struct `Layer` to be deserialized
void from_json(const json &j, Layer &layer) {
  j.at("width").get_to(layer.width);
  j.at("height").get_to(layer.height);
  j.at("tiles").get_to(layer.tiles);
}
