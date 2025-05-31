#pragma once
#include "core.hpp"
#include <cstdlib>
#include <raylib.h>
#include <string>
class DebugManager {
public:
  std::string inputText;
  std::string output;
  DebugManager() {
    output = "zEngine debug console v.";
    output = output + ZENGINE_VERSION;
    output += "\nType `help` for help\n";
  }
  void update() {
    char pressed = GetCharPressed();
    if (pressed != 0) {
      inputText.push_back(pressed);
    }
    if (IsKeyPressed(KEY_ENTER) && inputText.length() > 0) {
      output.push_back('>');
      output += inputText;
      output.push_back('\n');
      parseCommand();
      inputText.clear();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && inputText.length() > 0) {
      inputText.pop_back();
    }
  }
  void draw() {
    DrawRectangleV(Vector2{(float)GetScreenWidth() / 2.f + 10.f, 10.f},
                   Vector2{(float)GetScreenWidth() / 2.f - 20.f,
                           (float)GetScreenHeight() - 20.f},
                   GRAY);
    DrawRectangleLinesEx(Rectangle{(float)GetScreenWidth() / 2.f + 12.f, 12.f,
                                   (float)GetScreenWidth() / 2.f - 24.f,
                                   (float)GetScreenHeight() - 24.f},
                         5, BLACK);
    DrawRectangle(GetScreenWidth() / 2 + 20, GetScreenHeight() - 50,
                  GetScreenWidth() / 2 - 40, 30, WHITE);

    // draw console
    DrawText(output.c_str(), GetScreenWidth() / 2 + 21, 16, 20, BLACK);

    // draw input
    std::string drawnText = inputText;
    while (MeasureText(drawnText.c_str(), 28) > GetScreenWidth() / 2 - 50) {
      drawnText.erase(0, 1);
    }
    DrawText(drawnText.c_str(), GetScreenWidth() / 2 + 21,
             GetScreenHeight() - 51, 28, BLACK);
  }
  void parseCommand() {
    if (inputText == "help") {
      output += "Hello there!\n";
    } else if (inputText == "quitApp") {
      exit(0);
    } else {
      output += "unknown command\n";
    }
  }
};
