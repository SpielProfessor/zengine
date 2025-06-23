#include "raylib.h"
#include <cmath>

// Assuming you have a virtual resolution like 800x600
Vector2 GetVirtualMousePosition(int screenWidth, int screenHeight,
                                int virtualWidth, int virtualHeight) {
  Vector2 mouse = GetMousePosition();

  // Calculate the scale factor while preserving aspect ratio
  float scale = fminf((float)screenWidth / virtualWidth,
                      (float)screenHeight / virtualHeight);

  // Calculate the offset (black bars, letterboxing)
  float offsetX = (screenWidth - (virtualWidth * scale)) * 0.5f;
  float offsetY = (screenHeight - (virtualHeight * scale)) * 0.5f;

  // Apply inverse transformation to mouse coordinates
  float virtualX = (mouse.x - offsetX) / scale;
  float virtualY = (mouse.y - offsetY) / scale;

  return {virtualX, virtualY};
}
