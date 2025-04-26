#include "texture.hpp"
#include <raylib.h>
#include <stdio.h>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, TextureObject> TEXTURE_INDEX;
TextureObject::TextureObject(std::string path_) : path(path_) {}
TextureObject::TextureObject() {}
TextureObject::~TextureObject() {}
void TextureObject::build() {
  built = true;
  texture = LoadTexture(path.c_str());
}
Texture2D TextureObject::getTexture() {
  if (!built) {
    puts("[WARNING] cannot get a unbuilt texture");
  }
  return texture;
}
void unloadTextures() {
  for (auto pair : TEXTURE_INDEX) {
    if (IsTextureReady(pair.second.texture)) {
      UnloadTexture(pair.second.texture);
    }
  }
}

void initializeTexture(std::string id, std::string path) {
  TEXTURE_INDEX[id] = TextureObject(path);
  printf("Initializing %s\n", id.c_str());
}
void loadTextures() {
  for (auto &pair : TEXTURE_INDEX) {
    pair.second.build();
    printf("Building %s\n", pair.first.c_str());
    printf("ID: %d\n", pair.second.texture.id);
  }
}
