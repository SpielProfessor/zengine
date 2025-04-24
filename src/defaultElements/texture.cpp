#include "texture.hpp"
#include <raylib.h>
#include <string>
TextureHandle::TextureHandle(std::string path) { LoadTexture(path.c_str()); }
TextureHandle::TextureHandle() {}
TextureHandle::~TextureHandle() { UnloadTexture(texture); }
